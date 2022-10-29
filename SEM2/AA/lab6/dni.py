# epsilon = 1e-5
#
# inf = 1e10
#
#
# def vertical_check(plane):
#     return plane[0] == 0
#
# n = int(input())
#
# planes = []
#
# for _ in range(n):
#     coeffs = input().strip().split(" ")
#     planes.append((float(coeffs[0]), float(coeffs[1]), float(coeffs[2])))
#
# m = int(input())
#
# for k in range(m):
#     pointCoords = input().strip().split(" ")
#
#     point = [float(pointCoords[0]), float(pointCoords[1])]
#
#     maxim_x, maxim_y = inf, inf
#     minim_x, minim_y = -inf, -inf
#
#     for plane in planes:
#         if vertical_check(plane):
#             if (plane[2] + plane[1] * point[1]) >= 0:
#                 continue
#         else:
#             if (plane[2] + plane[0] * point[0]) >= 0:
#                 continue
#
#         if vertical_check(plane):
#
#             if -1 * plane[2] / plane[1] < point[1]:
#
#                 minim_y = max(minim_y, -1 * plane[2] / plane[1])
#             else:
#                 maxim_y = min(maxim_y, -1 * plane[2] / plane[1])
#         else:
#
#             if -1 * plane[2] / plane[0] < point[0]:
#
#                 minim_x = max(minim_x, -1 * plane[2] / plane[0])
#             else:
#                 maxim_x = min(maxim_x, -1 * plane[2] / plane[0])
#
#     if max(maxim_x, maxim_y) == inf or min(minim_x, minim_y) == -inf:
#         print("NO")
#     else:
#         area = (maxim_x - minim_x) * (maxim_y - minim_y)
#
#         if abs(float(area) - epsilon) <= int(area):
#             area = int(area)
#         print("YES")
#         print(area)

epsilon = 1e-5

inf = 1e10

nrPlanes = int(input())


xInfLim = yInfLim = -inf
xSupLim = ySupLim = inf

for _ in range(nrPlanes):
    coeffs = input().strip().split(" ")
    a, b, c = (float(coeffs[0]), float(coeffs[1]), float(coeffs[2]))
    supLim = inf
    infLim = -inf
    vertical = None

    if abs(a) <= epsilon:
        vertical = True
        if b > 0:
            supLim = -c / b
        elif b < 0:
            infLim = -c / b
    elif abs(b) <= epsilon:
        vertical = False
        if a > 0:
            supLim = -c / a
        elif a < 0:
            infLim = -c / a

    if vertical:
        yInfLim = max(yInfLim, infLim)
        ySupLim = min(ySupLim, supLim)
    else:
        xInfLim = max(xInfLim, infLim)
        xSupLim = min(xSupLim, supLim)

if xInfLim - epsilon > xSupLim or yInfLim - epsilon > ySupLim:

    print("VOID")
elif ((yInfLim != -inf and ySupLim != inf) and yInfLim - epsilon < ySupLim) and \
        ((xInfLim != -inf and xSupLim != inf) and xInfLim - epsilon < xSupLim):

    print("BOUNDED")
else:

    print("UNBOUNDED")



