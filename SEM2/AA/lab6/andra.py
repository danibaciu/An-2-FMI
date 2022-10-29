# import matplotlib.pyplot as plt
# import numpy as np
#
# # global variables
# F1 = 170000000 # 85k * 2000 lei/buc
# V1 = 352884.71
#
# F2 = 22100000 # 85k * 260 lei/buc
# V2 = 519802.5
#
#
# def f(n, option = "matritare"):
#     if option == "matritare" :
#         return F1 + n * V1
#     elif option == "turnare" :
#         return F2 + n * V2
#
#
# # setam axele la centru
# fig = plt.figure()
# ax = fig.add_subplot(1, 1, 1)
#
# x = np.linspace(0, 3000)
#
# # plotam functiile
# plt.plot(x, f(x) , 'r', label=f"Grafic Matritare : Cmatr = {F1} + 85000 * {V1}")
# plt.plot(x, f(x, "turnare") , 'b', label=f"Grafic Turnare : Cturn = {F2} + 85000 * {V2}")
#
# plt.title("Dependenta cost-număr de produse")
#
# ax.legend()
#
# # afisam graficul
# plt.show()

# nume, sum_of_data = "Baciu Daniel-Mihai", 0
#
# for charachter in nume:
#
#     print(f"{charachter} \t\t este codificat astfel : \t base 16 = {hex(ord(charachter))} \t| base 10 = {ord(charachter)} \t| base 2 = {format(ord(charachter), '#018b')[2:]}")
#
#     sum_of_data += ord(charachter)
#
# print("\n")
#
# print(f"Suma valorilor binare este : {format(sum_of_data, '#018b')[2:]}", end = "\n\n")
#
# print(f"Checksum-ul este complementul fata de 1 al sumei, adica este = {''.join(['1' if x == '0' else '0' for x in format(sum_of_data, '#018b')[2:]])}", end = "\n\n")

import sys
print(sys.byteorder)