import numpy as np
import pandas as pd
import time 
A_orig = np.array([
    [ 1,  4,  0,  6,  4,  3,  2,  2,  6,  5],   
    [ 2,  4,  6, -4,  7,  6, -3, -1,  4,  6],   
    [ 8,  2,  0, -5, -4,  9,  7,  4, -4,  9],   
    [ 1,  0,  2,  3,  4,  5, -3, -5,  0,  6],   
    [-2, -3, -5, -6, 10,  0,  0,  0, -4, -9],   
    [ 3,  1,  2,  5,  2,  4,  0,  5,  7,  9],   
    [ 3,  5,  6,  6, -4,  3,  5,  0,  3, -4],   
    [ 4,  5,  1,  2,  3,  5, -5, -3, -5, -2],   
    [ 1,  3,  3,  4,  9,  0,  5,  6,  7,  9],   
    [ 2,  6,  4,  2,  2,  0, -1,  4, -5, -6]    
], dtype=float)

b = np.array([25, 15, 16, -16, -3, 5, 14, 15, 4, 10], dtype=float)

#5 slack, 3 surplus, 5 artificial
A_M = np.zeros((10, 23))
A_M[:, :10] = A_orig
cols_sl = [10, 11, 12, 13, 14]
cols_sr = [15, 16, 17]
cols_as = [18, 19, 20, 21, 22]

def add(r, c, val):
    A_M[r, c] = val

sl_match = [0, 2, 4, 6, 7]
for i in range(5):
    add(sl_match[i], cols_sl[i], 1)

sr_match = [3, 5, 8]
for i in range(3):
    add(sr_match[i], cols_sr[i], -1)

as_match = [1, 3, 5, 8, 9]
for i in range(5):
    add(as_match[i], cols_as[i], 1)

col_names = ([f"x{i}" for i in range(1, 11)] + [f"sl{i}" for i in range(1, 6)] + [f"sr{i}" for i in range(1, 4)] + [f"A{i}" for i in range(1, 6)])
df = pd.DataFrame(A_M, columns = col_names)
df["b"] = b

print(df)
MX = -1e6
weights = np.array([1, 2, 3, 3, 4, -5, 2, 4, 5, -4])
w = np.zeros(23)
w[:10] = weights
for i in range(5):
    w[cols_as[i]] = MX
basis = np.array([10, 11, 12, 13, 14, 18, 19, 20, 21, 22])
def manual_simplex(A, b, c, basis):
    A = A.astype(float).copy()
    b = b.astype(float).copy()
    c = c.astype(float).copy()

    m, n = A.shape
    B = basis.copy()
    N = [j for j in range(n) if j not in B]

    T = np.zeros((m + 1, n + 1))
    T[1:, :n] = A # I'm gonna take the last col and make it b
    T[1:, -1] = b

    def update_row0():
        cB = c[B]
        z = cB @ T[1:, :n]          # z_j  
        z0 = cB @ T[1:, -1]         # current obj. value
        T[0, :n] = z - c            # row 0:  z_j - c_j
        T[0, -1] = z0

    tableau_hist = []

    update_row0()
    tableau_hist.append(T.copy())
    iteration = 0
    while True:
        iteration += 1
        enter_col = np.argmin(T[0, :-1])
        if T[0, enter_col] >= 0:       
            break

        col = T[1:, enter_col]
        positive_rows = np.where(col > 1e-12)[0]   # takes the first and only thing from the tuple
        if positive_rows.size == 0:
            raise RuntimeError("LP is unbounded in column %d" % enter_col)

        ratios = np.divide(T[1:, -1], col,
                   out=np.full_like(col, np.inf, dtype=float),
                   where=col > 0)
        leave_row_rel = np.argmin(ratios)
        leave_row = leave_row_rel + 1          # +1 to account for row‑0

        pivot = T[leave_row, enter_col]
        T[leave_row, :] /= pivot               
        for r in range(T.shape[0]): #how many rows
            if r != leave_row: 
                T[r, :] -= T[r, enter_col] * T[leave_row, :] #which is just 1
        B[leave_row_rel] = enter_col   # put entering var into the basis
        update_row0()                  # fresh reduced–cost row
        tableau_hist.append(T.copy())  
 
    x = np.zeros(n)
    for r, var in enumerate(B):
        x[var] = T[r+1, -1]

    z_opt = T[0, -1]
    return x, z_opt, tableau_hist, iteration
start = time.perf_counter()

a, b, c, d = manual_simplex(A_M, b, w, basis)

elapsed = time.perf_counter() - start
var_names = (
    [f"x{i}" for i in range(1, 11)] +
    [f"sl{i}" for i in range(1, 6)] +
    [f"sr{i}" for i in range(1, 4)] +
    [f"A{i}" for i in range(1, 6)] +
    ["RHS"]
)

for k, tab in enumerate(c):
    df_tab = pd.DataFrame(np.round(tab, 6), columns=var_names)
    df_tab.index = ["Obj"] + [f"Row{r+1}" for r in range(10)]
    print(f"tableau{k}", df_tab)
print(b)        
print(d)
print(elapsed)