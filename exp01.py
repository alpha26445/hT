class TeleBook:
    def __init__(self, name, tele):
        self.name = name
        self.tele = tele

def insert_records(hashtable=None):
    if hashtable is None:  # Only create new table if not passed
        hashtable = [None for i in range(10)]

    records = int(input("Enter the number of records: "))

    for i in range(records):
        name = input("Enter name: ")
        tele = int(input("Enter telephone number: "))
        hashvalue = tele % 10

        if hashtable[hashvalue] is None:
            hashtable[hashvalue] = TeleBook(name, tele)
        else:
            for j in range(len(hashtable)):  # <-- your original unchanged loop
                nhashvalue = (hashvalue + j**2) % 10
                if hashtable[nhashvalue] is None:
                    hashtable[nhashvalue] = TeleBook(name, tele)
                    break
            else:
                print("Hash table is full! Could not insert:", name)

    return hashtable

def display_records(hash1):
    print("\n--- Stored Records ---")
    for idx, obj in enumerate(hash1):
        if obj is not None:
            print(idx, obj.name, obj.tele)
    print()

def search_records(hash1):
    toSearch = input("Enter the name to search: ")
    for i in hash1:
        if i is not None and i.name == toSearch:
            print("Name found:", i.name, i.tele)
            return
    print("Name not found")

def main():
    hash1 = [None for _ in range(10)]  # Initialize empty hash table

    while True:
        print("\n***** Menu *****")
        print("1. Insert Records")
        print("2. Display Records")
        print("3. Search in Records")
        print("4. Exit")

        choice = int(input("Enter choice: "))

        if choice == 4:
            print("Exiting program")
            break
        elif choice == 1:
            hash1 = insert_records(hash1)
        elif choice == 2:
            display_records(hash1)
        elif choice == 3:
            search_records(hash1)
        else:
            print("Invalid choice, Try again")

main()
