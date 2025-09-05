# 矩阵格式，a * b, 表示每个元素是否可能非零
a = [[1, 1, 1, 1, 1, 1, 1],
     [0, 1, 1, 1, 1, 1, 1],
     [0, 0, 1, 1, 1, 1, 1],
     [0, 0, 0, 1, 1, 1, 1],
     [0, 0, 0, 0, 1, 1, 1],
     [0, 0, 0, 0, 0, 1, 1],
     [0, 0, 0, 0, 0, 0, 1],
     ]
b = [[1, 1, 1, 1, 1, 1, 1],
     [0, 1, 1, 1, 1, 1, 1],
     [0, 0, 1, 1, 1, 1, 1],
     [0, 0, 0, 1, 1, 1, 1],
     [0, 0, 0, 0, 1, 1, 1],
     [0, 0, 0, 0, 0, 1, 1],
     [0, 0, 0, 0, 0, 0, 1],
     ]
name = ["res", "x", "y"]
give = []
mod = 0  # 是否取模
f = open("out.txt", 'w')
for i in range(len(a)):
    for j in range(len(b[0])):
        s = ""
        if mod: 
            s += "("
        flag = 0
        for k in range(len(a[0])):
            if a[i][k] == 0 or b[k][j] == 0: 
                continue
            s += f"{name[1]}[{i}][{k}] * {name[2]}[{k}][{j}]"
            flag = 1
            if mod: 
                s += " % mod"
            s += " + "
        if not flag: 
            continue
        s = s[:-3]
        if mod: 
            s += ") % mod"
        s += ';'
        s =  f"{name[0]}[{i}][{j}] = {s}"
        print(s)
        f.write(s + '\n')
for i in give:
    print(i)
    f.write(i + '\n')

