import z3

solver = z3.Solver()
x,y,z,dx,dy,dz = z3.Ints('x y z dx dy dz')

f = open("in", "r")
for line in f:
	parts = line.split('@')

	xyz_str = parts[0].split(',')
	dxdydz_str = parts[1].split(',')

	x1, y1, z1 = [int(num.strip()) for num in xyz_str]
	dx1, dy1, dz1 = [int(num.strip()) for num in dxdydz_str]

	solver.add((x1 - x) * (dy - dy1) == (dx - dx1) * (y1 - y))
	solver.add((y1 - y) * (dz - dz1) == (dy - dy1) * (z1 - z))
	solver.add((z1 - z) * (dx - dx1) == (dz - dz1) * (x1 - x))
	solver.add((x1 - x) / (dx - dx1) >= 0)

solver.check()
print(solver.model())
print(solver.model()[x].as_long() + solver.model()[y].as_long() + solver.model()[z].as_long())
