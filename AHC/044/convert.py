file_index = int(input("Enter file index: "))
file_name = f"AHC/044/tools_x86_64-pc-windows-gnu/out/{file_index:04d}.txt"

with open(file_name, "r") as file:
    input_data = file.read()

lines = input_data.strip().split("\n")
formatted_lines = [
    f"{i} {x.split()[0]}\n{i} {x.split()[1]}" for i, x in enumerate(lines)
]

output = "\n".join(formatted_lines)
print(100, 200)
print(output)
