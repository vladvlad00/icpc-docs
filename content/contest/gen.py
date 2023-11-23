import sys

from random import randint, choice, shuffle, uniform, sample
from math import gcd, sqrt
from string import ascii_lowercase, ascii_uppercase

chars = ['0', '1']

def random_string(n, chars = ascii_lowercase):
	return "".join([choice(chars) for _ in range(n)])

def print_list(l, sep = " "):
	print(sep.join([str(item) for item in l]))

def gen_graph_edges(n, m):
	edges = []
	for i in range(1, n):
		edges.append((randint(0, i - 1), i))
	for nr in range(n, m + 1):
		edges.append((randint(0, n - 1), randint(0, n - 1)))
	return edges

