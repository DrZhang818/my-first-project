import random
import os

def generate_test_data():
    sizes = [100, 1000, 10000, 100000]
    folder = "data"

    if not os.path.exists(folder):
        os.makedirs(folder)

    for n in sizes:
        filename = os.path.join(folder, f"input_{n}.txt")
        with open(filename, "w") as f:
            f.write(f"{n}\n")
            data = [random.randint(-1000, 1000) for _ in range(n)]
            f.write(" ".join(map(str, data)))
        print(f"Generate: {filename}")

if __name__ == "__main__":
    generate_test_data()