# Concept Options — Pipe Inspection Robot (Ø150–200 mm)

## Shared envelope & pipe model
- Pipe IDs: 150–200 mm → Pipe radii: R150 = 75 mm, R200 = 100 mm
- Robot max OD: 140 mm (for Ø200 pipe) with ≥ 5 mm wall clearance
- Keep-in radius: Rkeep = Rpipe − clearance
- Target wheel/track contact radius (from center): Rc ≈ Rpipe − 5 mm

---

## Concept A — Tri-Wheel, Spring-Loaded Arms (Self-Centering, 120° apart)
**Kinematics**: 3 identical radial arms at 0°/120°/240°, each with a pivot at the center hub, torsion/compression spring provides preload; wheels at arm tips.

**Pros**
- Automatic centering across 150–200 mm pipes
- Fewer parts, fast to assemble
- Maintains near-constant normal force with simple springs

**Cons**
- Arm pivots carry all impact loads
- Camera packaging in the centerline needs a raised nose

**When to choose**
- Mixed pipe diameters, quick build, robust traction on bends

---

## Concept B — 4-Wheel Symmetric (Twin Rocker or Fixed Bogies)
**Kinematics**: 2×2 wheels on left/right frames; either fixed plates or a passive rocker link for equalized contact.

**Pros**
- Stable for verticals (bigger support polygon)
- Simple rectangular chassis, easy electronics mounting

**Cons**
- Less self-centering across large ID variation
- More width; risk of corner rub in tight bends

**When to choose**
- Mostly single-diameter pipes; prioritize easy packaging

---

## Concept C — Micro-Tracked (Twin Tracks with Idler Tension)
**Kinematics**: Each side has a drive sprocket + idler + short track; optional small bogies behind the belt.

**Pros**
- High traction on dirty or wet pipes
- Smooth ride over small gaps and pits

**Cons**
- Packaging/tensioning complexity
- Debris ingress into track; more maintenance

**When to choose**
- Low-friction pipes, debris expected, must-do vertical climbs
