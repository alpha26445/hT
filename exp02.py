def hash_function(key, size):
    return hash(key) % size

def insert(table, size, key, value):
    index = hash_function(key, size)
    for i in range(len(table[index])):
        if table[index][i][0] == key:
            table[index][i] = (key, value)
            print("Updated:", key, value)
            return
    table[index].append((key, value))
    print("Inserted:", key, value)

def find(table, size, key):
    index = hash_function(key, size)
    for pair in table[index]:
        if pair[0] == key:
            print("Key found:", key, pair[1])
            return
    print("Key not found")

def delete(table, size, key):
    index = hash_function(key, size)
    for i in range(len(table[index])):
        if table[index][i][0] == key:
            del table[index][i]
            print("Deleted key:", key)
            return
    print("Key not found")

def display(table):
    print("\n--- Hash Table ---")
    for i in range(len(table)):
        print(f"Index {i}:", end=" ")
        if table[i]:
            for pair in table[i]:
                print(f"({pair[0]}, {pair[1]})", end=" -> ")
            print("None")
        else:
            print("Empty")

def main():
    size = 10
    table = [[] for i in range(size)]
    while True:
        print("\n***** MENU *****")
        print("1. Insert")
        print("2. Search")
        print("3. Delete")
        print("4. Display")
        print("5. Exit")
        choice = int(input("Enter choice: "))

        if choice == 1:
            key = input("Enter key to insert: ")
            value = input("Enter value to insert: ")
            insert(table, size, key, value)
        elif choice == 2:
            key = input("Enter key to search: ")
            find(table, size, key)
        elif choice == 3:
            key = input("Enter key to delete: ")
            delete(table, size, key)
        elif choice == 4:
            display(table)
        elif choice == 5:
            print("Exiting program.")
            break
        else:
            print("Invalid choice. Try again.")

main()
