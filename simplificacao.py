import sympy as sp
import sympy as sp
import sympy as sp

x, y = sp.symbols("x y")


x, y = sp.symbols("x y")
equation = sp.sqrt(0.504) + y + x + x - 0.846 + sp.sqrt(y + y - 0.162) ** 0.504 + y + x - y + 0.378 + y - 0.792 - 0.432 ** y * sp.tanh(sp.sin(y / 0.522) + y - 0.432 / y - 0.9 + y - 0.504 * 0.738 - 0.414 * sp.exp(-0.81) ** y * sp.sin(y + y) * 0.432 * sp.exp(y - 0.504 + 0.54) * sp.exp(y - 0.432) ** x - y * x / -0.81 ** 0.162 * y ** x ** -0.216 - 0.162 - x + y + y + x - 0.432 ** -0.504 - x + x - y + y + y - 0.792 - 0.432 + y + y - 0.432 ** y ** y / x + x - 0.126 + y * 0.432 * sp.exp(x + x) / 0.666 * x - x * -0.432 + x + y - y * y * sp.exp(-0.81) ** -0.63 * x + sp.sin(y + y) - 0.504 + 0.54 * sp.exp(-0.162) - -0.432 ** x - y + y - 0.792 ** x ** 0.504 * 0.288 - 0.162 - x * -0.432 ** x ** x + x - y * x / 0.81 ** 0.342 * sp.exp(-0.234) ** y + x ** y - 0.162 - 0.432 + x + y - y * 0.432 * sp.exp(-0.81)
final = sp.simplify(equation)

print(final)
