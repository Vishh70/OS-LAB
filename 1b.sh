#!/bin/bash

# File to store records
FILE="1b.txt"

while true
do
    echo ""
    echo "========== ADDRESS BOOK MENU =========="
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"
    echo "======================================="
    read -p "Enter your choice: " choice

    case $choice in
        1)
            > $FILE
            echo "Address book created (cleared old data)."
            ;;
        2)
            if [ -s $FILE ]; then
                echo "----- Address Book Contents -----"
                cat $FILE
                echo "---------------------------------"
            else
                echo "Address book is empty or not created yet."
            fi
            ;;
        3)
            read -p "Enter Name: " name
            read -p "Enter Phone: " phone
            read -p "Enter Email: " email
            echo "$name | $phone | $email" >> $FILE
            echo "Record inserted successfully."
            ;;
        4)
            read -p "Enter Name to delete: " name
            if grep -q "$name" $FILE; then
                grep -v "$name" $FILE > temp.txt && mv temp.txt $FILE
                echo "Record deleted successfully."
            else
                echo "No record found for '$name'."
            fi
            ;;
        5)
            read -p "Enter Name to modify: " name
            if grep -q "$name" $FILE; then
                echo "Enter new details:"
                read -p "Enter new Phone: " phone
                read -p "Enter new Email: " email
                grep -v "$name" $FILE > temp.txt
                echo "$name | $phone | $email" >> temp.txt
                mv temp.txt $FILE
                echo "Record modified successfully."
            else
                echo "No record found for '$name'."
            fi
            ;;
        6)
            echo "Exiting Address Book..."
            exit 0
            ;;
        *)
            echo "Invalid choice. Try again."
            ;;
    esac
done
