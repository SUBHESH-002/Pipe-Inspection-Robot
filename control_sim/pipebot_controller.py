"""
control_sim/pipebot_controller.py
Active-Omni PipeBot — Kinematics Simulator

Simulates body motion (vx, vy, wz) for the two-wheel active-omni module
and converts to motor speeds (oh1, oh2, oc1, oc2). Integrates pose over time,
plots results, and saves a CSV for analysis.

Usage (from repo root):
    python3 control_sim/pipebot_controller.py

Outputs:
    control_sim/sim_results.csv
    control_sim/plot_vx_vy_wz.png
    control_sim/plot_motor_speeds.png
"""

import math
import csv
import os
from dataclasses import dataclass
import numpy as np
import matplotlib.pyplot as plt


# ------------------------------
# Parameters (EDIT AS NEEDED)
# ------------------------------
@dataclass
class BotParams:
    Rh: float = 0.025   # hub radius [m]
    rr: float = 0.008   # roller radius [m]
    alpha_deg: float = 45.0
    G: float = 1.50     # central:roller gear ratio
    B: float = 0.10     # track width [m]

    def kappa(self) -> float:
        return self.G * self.rr * math.cos(math.radians(self.alpha_deg))


@dataclass
class SimParams:
    dt: float = 0.01            # time step [s]
    t_final: float = 10.0       # total sim time [s]
    seed: int = 42
    # Optional actuator limits (RPM). Used only to clamp outputs.
    hub_max_rpm: float = 180.0
    cen_max_rpm: float = 300.0


# ------------------------------
# Kinematics
# ------------------------------
def inv_kin_two_wheel(vx, vy, wz, Rh, kappa, B):
    """Inverse kinematics: (vx, vy, wz) -> (oh1, oh2, oc1, oc2) [rad/s]."""
    Rh = max(Rh, 1e-9)
    kappa = kappa if abs(kappa) > 1e-12 else 1e-12

    oh1 = (vx / Rh) - (B * wz) / (2.0 * Rh)
    oh2 = (vx / Rh) + (B * wz) / (2.0 * Rh)

    vy_over_k = vy / kappa
    oc1 = oh1 + vy_over_k
    oc2 = oh2 + vy_over_k
    return oh1, oh2, oc1, oc2


def fwd_kin_two_wheel(oh1, oh2, oc1, oc2, Rh, kappa, B):
    """Forward kinematics: motor speeds -> body (vx, vy, wz)."""
    vx = (Rh / 2.0) * (oh1 + oh2)
    vy = (kappa / 2.0) * ((oc1 - oh1) + (oc2 - oh2))
    wz = (Rh / B) * (oh2 - oh1)
    return vx, vy, wz


# ------------------------------
# Command Profiles
# ------------------------------
def profile(t):
    """
    Define body-frame command (vx, vy, wz) vs time.
    Feel free to customize for your tests.
    """
    # 0–3 s: straight
    if t < 3.0:
        return 0.05, 0.00, 0.00
    # 3–6 s: pure sideways
    if t < 6.0:
        return 0.00, 0.02, 0.00
    # 6–8 s: spin in place
    if t < 8.0:
        return 0.00, 0.00, 0.5
    # 8–10 s: gentle helix
    return 0.04, 0.01, 0.15


# ------------------------------
# Simulation
# ------------------------------
def simulate(bot: BotParams, sim: SimParams):
    np.random.seed(sim.seed)
    kappa = bot.kappa()

    steps = int(sim.t_final / sim.dt)
    t = np.linspace(0.0, sim.t_final, steps + 1)

    # State (body-frame pose for convenience):
    # x: along pipe axis, y: circumferential arc length, psi: roll about pipe axis
    x = np.zeros_like(t)
    y = np.zeros_like(t)
    psi = np.zeros_like(t)

    # Cmd and motor logs
    vx_cmd = np.zeros_like(t)
    vy_cmd = np.zeros_like(t)
    wz_cmd = np.zeros_like(t)

    oh1 = np.zeros_like(t)
    oh2 = np.zeros_like(t)
    oc1 = np.zeros_like(t)
    oc2 = np.zeros_like(t)

    # Simulate
    for k in range(steps):
        vx, vy, wz = profile(t[k])
        vx_cmd[k], vy_cmd[k], wz_cmd[k] = vx, vy, wz

        h1, h2, c1, c2 = inv_kin_two_wheel(vx, vy, wz, bot.Rh, kappa, bot.B)

        # Convert to RPM for optional saturation then back to rad/s
        h1_rpm = (h1 * 60.0) / (2.0 * math.pi)
        h2_rpm = (h2 * 60.0) / (2.0 * math.pi)
        c1_rpm = (c1 * 60.0) / (2.0 * math.pi)
        c2_rpm = (c2 * 60.0) / (2.0 * math.pi)

        h1_rpm = float(np.clip(h1_rpm, -sim.hub_max_rpm, sim.hub_max_rpm))
        h2_rpm = float(np.clip(h2_rpm, -sim.hub_max_rpm, sim.hub_max_rpm))
        c1_rpm = float(np.clip(c1_rpm, -sim.cen_max_rpm, sim.cen_max_rpm))
        c2_rpm = float(np.clip(c2_rpm, -sim.cen_max_rpm, sim.cen_max_rpm))

        h1 = (h1_rpm * 2.0 * math.pi) / 60.0
        h2 = (h2_rpm * 2.0 * math.pi) / 60.0
        c1 = (c1_rpm * 2.0 * math.pi) / 60.0
        c2 = (c2_rpm * 2.0 * math.pi) / 60.0

        oh1[k], oh2[k], oc1[k], oc2[k] = h1, h2, c1, c2

        # Optionally add tiny execution noise (comment out if not needed)
        # h1 += np.random.randn() * 0.02
        # h2 += np.random.randn() * 0.02
        # c1 += np.random.randn() * 0.03
        # c2 += np.random.randn() * 0.03

        vx_eff, vy_eff, wz_eff = fwd_kin_two_wheel(h1, h2, c1, c2, bot.Rh, kappa, bot.B)

        # Integrate pose (simple Euler in body frame)
        x[k+1]   = x[k]   + vx_eff * sim.dt
        y[k+1]   = y[k]   + vy_eff * sim.dt
        psi[k+1] = psi[k] + wz_eff * sim.dt

    # Last command sample fill
    vx_cmd[-1], vy_cmd[-1], wz_cmd[-1] = profile(t[-1])
    oh1[-1], oh2[-1], oc1[-1], oc2[-1] = oh1[-2], oh2[-2], oc1[-2], oc2[-2]

    return {
        "t": t, "x": x, "y": y, "psi": psi,
        "vx_cmd": vx_cmd, "vy_cmd": vy_cmd, "wz_cmd": wz_cmd,
        "oh1": oh1, "oh2": oh2, "oc1": oc1, "oc2": oc2
    }


# ------------------------------
# Save & Plot
# ------------------------------
def save_csv(path, data):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["t","x","y","psi","vx_cmd","vy_cmd","wz_cmd","oh1","oh2","oc1","oc2"])
        for i in range(len(data["t"])):
            w.writerow([
                data["t"][i], data["x"][i], data["y"][i], data["psi"][i],
                data["vx_cmd"][i], data["vy_cmd"][i], data["wz_cmd"][i],
                data["oh1"][i], data["oh2"][i], data["oc1"][i], data["oc2"][i]
            ])


def plot_signals(path_prefix, data):
    os.makedirs(os.path.dirname(path_prefix), exist_ok=True)

    # Plot commanded body velocities
    plt.figure(figsize=(8,4.5))
    plt.plot(data["t"], data["vx_cmd"], label="vx [m/s]")
    plt.plot(data["t"], data["vy_cmd"], label="vy [m/s]")
    plt.plot(data["t"], data["wz_cmd"], label="wz [rad/s]")
    plt.xlabel("Time [s]"); plt.ylabel("Commanded velocities")
    plt.title("Body-frame Commands")
    plt.legend(); plt.tight_layout()
    plt.savefig(path_prefix + "plot_vx_vy_wz.png", dpi=160)
    plt.close()

    # Plot motor speeds (rad/s)
    plt.figure(figsize=(8,4.5))
    plt.plot(data["t"], data["oh1"], label="oh1 (hub L)")
    plt.plot(data["t"], data["oh2"], label="oh2 (hub R)")
    plt.plot(data["t"], data["oc1"], label="oc1 (cen L)")
    plt.plot(data["t"], data["oc2"], label="oc2 (cen R)")
    plt.xlabel("Time [s]"); plt.ylabel("Motor speeds [rad/s]")
    plt.title("Motor Speeds")
    plt.legend(); plt.tight_layout()
    plt.savefig(path_prefix + "plot_motor_speeds.png", dpi=160)
    plt.close()


# ------------------------------
# Main
# ------------------------------
if __name__ == "__main__":
    bot = BotParams()
    sim = SimParams()

    data = simulate(bot, sim)
    save_csv("control_sim/sim_results.csv", data)
    plot_signals("control_sim/", data)

    print("Saved: control_sim/sim_results.csv")
    print("Saved: control_sim/plot_vx_vy_wz.png")
    print("Saved: control_sim/plot_motor_speeds.png")
