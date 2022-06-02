/*
This is a Online Medical Shop Software.

It can handle the following list of entities-
1. Manufacturers
2. Customers
3. Products
4. Shops/Warehouses
5. Delivery Agent

Each entitiy can be identified by its unique ID which is meant to be provided to by the user of this software while creating the different entities.

Some basic Features-
1. Can help you manage all the entities - Creating, Deleting and Printing.
2. You can add a Product to its specified Manufacturer.
3. You can add a Product with the specified Quantity to a Shop/Warehouse.
4. Customers can place their order in it.
5. Customers can get to know their order history.
6. Customers can see the inventory of a particular Shop/Warehouse.
7. Shopkeepers can get to know the Products offered by different Manufacturers
*/

import java.util.Scanner;//imported java util scanner for reading from the console
import java.util.ArrayList;//imported java util ArrayList for storing of entities
import java.util.HashSet;//imported java util HashSet for storing the Products manufactured by a manufacturer
import java.util.Set;//imported java util Set for storing the Products manufactured by a manufacturer

//Master class for our Software
public class OnlineMedicalShop {
    static final int SIZE = 100;

    // function to clear the console
    public static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    // class for storing Pair entity as (Product,Quantity)
    static class Pair {
        public Product product;
        public int quantity;

        public Pair() {
            this.product = null;
            this.quantity = 0;
        }
    }

    // Driver function
    public static void main(String[] args) {
        ArrayList<Manufacturer> manufacturer_list = new ArrayList<>();// ArrayList for storing Manufacturer
        ArrayList<Customer> customer_list = new ArrayList<>();// ArrayList for storing Customers
        ArrayList<Product> product_list = new ArrayList<>();// ArrayList for storing Products
        ArrayList<Shop> shop_list = new ArrayList<>();// ArrayList for storing Shops/Warehouses
        ArrayList<Delivery> delivery_list = new ArrayList<>();// ArrayList for storing Delivery Agent
        int input;
        Scanner scan = new Scanner(System.in);// initializing the Scanner
        do {
            clearScreen();
            // Printing the menu
            System.out.print("Welcome to our Online Medical Shop\n\n" +
                    "1. Create, delete and print entities\n" +
                    "2. Add a product to manufacturer\n" +
                    "3. Add product to a shop\n" +
                    "4. Order a product\n" +
                    "5. List all purchases made by a customer\n" +
                    "6. List inventory of a shop\n" +
                    "7. List products made by a manufacturer\n" +
                    "8. Exit\n" +
                    "Enter your choice: ");
            input = scan.nextInt();
            // Basic switch-case to perform the required tasks
            switch (input) {
                case 1:
                    clearScreen();
                    // Printing the sub-menu
                    System.out.print("What would you like to do?\n" +
                            "1. Create an entity\n" +
                            "2. Delete an entity\n" +
                            "3. Print Entities\n" +
                            "Enter your choice : ");
                    int choice = scan.nextInt();
                    // switch-case for sub-menu
                    switch (choice) {
                        case 1:
                            clearScreen();
                            // Printing the sub-sub-menu
                            System.out.print("Which type of entity would you like to create?\n" +
                                    "1. Manufacturer\n" +
                                    "2. Customer\n" +
                                    "3. Product\n" +
                                    "4. Shops and Warehouses\n" +
                                    "5. Delivery agent\n" +
                                    "Enter your Choice : ");
                            int subChoice = scan.nextInt();
                            // switch-case for sub-sub-menu
                            switch (subChoice) {
                                case 1:
                                    // adding the new manufacturer given as input to the manufacturer list
                                    manufacturer_list.add(new Manufacturer(scan));
                                    System.out.println("Added successfully...");
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    break;
                                case 2:
                                    // adding the new customer given as input to the customer list
                                    customer_list.add(new Customer(scan));
                                    System.out.println("Added successfully...");
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                                    break;
                                case 3:
                                    // adding the new product given as input to the product list
                                    product_list.add(new Product(scan));
                                    System.out.println("Added successfully...");
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    break;
                                case 4:
                                    // adding a new shop/warehouse given as input to the shop/warehouse list
                                    shop_list.add(new Shop(scan));
                                    System.out.println("Added successfully...");
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                                    break;
                                case 5:
                                    // adding a new delivery agent given as input to the delivery agent list
                                    delivery_list.add(new Delivery(scan));
                                    System.out.println("Added successfully...");
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                                    break;
                                default:
                                    // output an error message if the input is not in the menu
                                    System.out.println("You have entered a wrong choice.\nPlease try again...");
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                            }
                            break;
                        case 2:
                            clearScreen();
                            // Printing the sub-sub-menu
                            System.out.print("Which tyye of entity would you like to delete?\n" +
                                    "1. Manufacturer\n" +
                                    "2. Customer\n" +
                                    "3. Product\n" +
                                    "4. Shops and Warehouses\n" +
                                    "5. Delivery agent\n" +
                                    "Enter your Choice : ");
                            subChoice = scan.nextInt();
                            // switch-case for sub-sub-menu
                            switch (subChoice) {
                                case 1:
                                    clearScreen();
                                    // output the list of manufacturers in a tabular form
                                    System.out.printf("%20s\t%20s\n", "Manufacturer ID", "Manufacturer Name");
                                    for (Manufacturer MF : manufacturer_list) {
                                        System.out.printf("%20d\t%20s\n", MF.Id, MF.name);
                                    }
                                    // taking input the manufacturer ID which we want to delete
                                    System.out.print("Enter Manufacturer ID you want to delete : ");
                                    int id = scan.nextInt();
                                    boolean found = false;
                                    // linear search for manufacturer in the manufacturers list
                                    for (Manufacturer mf : manufacturer_list) {
                                        if (mf.Id == id) {
                                            found = true;
                                            // making the manufacturer data for the corresponding manufacturer's product
                                            // to be null
                                            for (Product p : mf.products) {
                                                for (Product P : product_list) {
                                                    if (p.Id == P.Id) {
                                                        P.manufacturer = null;
                                                        break;
                                                    }
                                                }
                                            }
                                            // removing the manufacturer
                                            manufacturer_list.remove(mf);
                                            System.out.println("Succesfully Removed...");
                                            break;
                                        }
                                    }
                                    if (!found) {
                                        System.out.println("Wrong ID...!!");
                                    }
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                                    break;
                                case 2:
                                    clearScreen();
                                    // output the list of customers in a tabular form
                                    System.out.printf("%20s\t%20s\n", "Customer ID", "Customer Name");
                                    for (Customer CH : customer_list) {
                                        System.out.printf("%20d\t%20s\n", CH.Id, CH.name);
                                    }
                                    // taking input the customer ID which we want to delete
                                    System.out.print("Enter the Customer ID you want to remove : ");
                                    id = scan.nextInt();
                                    found = false;
                                    // linear search for customer in the customers list
                                    for (Customer c : customer_list) {
                                        if (c.Id == id) {
                                            // removing the customer
                                            found = true;
                                            customer_list.remove(c);
                                            System.out.println("Succesfully Removed...");
                                            break;
                                        }
                                    }
                                    if (!found) {
                                        System.out.println("Wrong ID...!!");
                                    }
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                                    break;
                                case 3:
                                    clearScreen();
                                    // output the list of products in a tabular form
                                    System.out.printf("%20s\t%20s\n", "Product ID", "Product Name");
                                    for (Product P : product_list) {
                                        System.out.printf("%20d\t%20s\n", P.Id, P.name);
                                    }
                                    // taking input the product ID which we want to delete
                                    System.out.print("Enter the Product ID you want to remove : ");
                                    id = scan.nextInt();
                                    found = false;
                                    // linear search for product in the customer list
                                    for (Product p : product_list) {
                                        if (p.Id == id) {
                                            found = true;
                                            Manufacturer mf = p.manufacturer;
                                            // removing the product from the manufacturer's products list
                                            for (Manufacturer m : manufacturer_list) {
                                                if (mf.Id == m.Id) {
                                                    for (Product prod : m.products) {
                                                        if (prod.Id == p.Id) {
                                                            m.products.remove(prod);
                                                            break;
                                                        }
                                                    }
                                                    break;
                                                }
                                            }
                                            // removing the product
                                            product_list.remove(p);
                                            System.out.println("Succesfully Removed...");
                                            break;
                                        }
                                    }
                                    if (!found) {
                                        System.out.println("Wrong ID...!!");
                                    }
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                                    break;
                                case 4:
                                    clearScreen();
                                    // output the list of shops/warehouses in a tabular form
                                    System.out.printf("%20s\t%20s\n", "Shop ID", "Shop Name");
                                    for (Shop S : shop_list) {
                                        System.out.printf("%20d\t%20s\n", S.Id, S.name);
                                    }
                                    // taking input the shop/warehouse ID which we want to delete
                                    System.out.print("Enter the Shop OR Warehouse ID you want to remove : ");
                                    id = scan.nextInt();
                                    found = false;
                                    // linear search for shop/warehouse in the shops/warehouses list
                                    for (Shop s : shop_list) {
                                        if (s.Id == id) {
                                            found = true;
                                            // removing the shop/warehouse
                                            shop_list.remove(s);
                                            System.out.println("Succesfully Removed...");
                                            break;
                                        }
                                    }
                                    if (!found) {
                                        System.out.println("Wrong ID...!!");
                                    }
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                                    break;
                                case 5:
                                    clearScreen();
                                    // output the list of delivery agents in a tabular form
                                    System.out.printf("%20s\t%20s\n", "Delivery agent ID", "Delivery agent Name");
                                    for (Delivery D : delivery_list) {
                                        System.out.printf("%20d\t%20s\n", D.Id, D.name);
                                    }
                                    // taking input the delivery agent ID which we want to delete
                                    System.out.print("Enter the Delivery agent ID you want to remove : ");
                                    id = scan.nextInt();
                                    found = false;
                                    // linear search for delivery agent in the delivery agents list
                                    for (Delivery d : delivery_list) {
                                        if (d.Id == id) {
                                            found = true;
                                            // removing the delivery agent
                                            delivery_list.remove(d);
                                            System.out.println("Succesfully Removed...");
                                            break;
                                        }
                                    }
                                    if (!found) {
                                        System.out.println("Wrong ID...!!");
                                    }
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                                    break;
                                default:
                                    // output an error message if the input is not in the menu
                                    System.out.println("You have entered a wrong choice.\nPlease try again...");
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                            }
                            break;
                        case 3:
                            clearScreen();
                            // Printing the sub-sub-menu
                            System.out.print("Which tyye of entity would you like to print?\n" +
                                    "1. Manufacturer\n" +
                                    "2. Customer\n" +
                                    "3. Product\n" +
                                    "4. Shops and Warehouses\n" +
                                    "5. Delivery agent\n" +
                                    "Enter your Choice : ");
                            subChoice = scan.nextInt();
                            // switch-case for sub-sub-menu
                            switch (subChoice) {
                                case 1:
                                    clearScreen();
                                    // printing the manufacturers currently in the list in a tabular form
                                    System.out.printf("%20s\t%20s\n", "Manufacturer ID", "Manufacturer Name");
                                    for (Manufacturer MF : manufacturer_list) {
                                        System.out.printf("%20d\t%20s\n", MF.Id, MF.name);
                                    }
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                                    break;
                                case 2:
                                    clearScreen();
                                    // printing the customers currently in the list in a tabular form
                                    System.out.printf("%20s\t%20s\n", "Customer ID", "Customer Name");
                                    for (Customer CH : customer_list) {
                                        System.out.printf("%20d\t%20s\n", CH.Id, CH.name);
                                    }
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                                    break;
                                case 3:
                                    clearScreen();
                                    // printing the products currently in the list in a tabular form
                                    System.out.printf("%20s\t%20s\n", "Product ID", "Product Name");
                                    for (Product P : product_list) {
                                        System.out.printf("%20d\t%20s\n", P.Id, P.name);
                                    }
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                                    break;
                                case 4:
                                    clearScreen();
                                    // printing the shops/warehouses currently in the list in a tabular form
                                    System.out.printf("%20s\t%20s\n", "Shop ID", "Shop Name");
                                    for (Shop S : shop_list) {
                                        System.out.printf("%20d\t%20s\n", S.Id, S.name);
                                    }
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                                    break;
                                case 5:
                                    clearScreen();
                                    // printing the delivery agents currently in the list in a tabular form
                                    System.out.printf("%20s\t%20s\n", "Delivery agency ID", "Delivery agency Name");
                                    for (Delivery D : delivery_list) {
                                        System.out.printf("%20d\t%20s\n", D.Id, D.name);
                                    }
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                                    break;
                                default:
                                    // output an error message if the input is not in the menu
                                    System.out.println("You have entered a wrong choice.\nPlease try again...");
                                    System.out.print("Press Enter to continue...");
                                    scan.nextLine();
                                    scan.nextLine();
                            }
                            break;
                        default:
                            // output an error message if the input is not in the menu
                            System.out.println("You have entered a wrong choice.\nPlease try again...");
                            System.out.print("Press Enter to continue...");
                            scan.nextLine();
                            scan.nextLine();
                    }
                    break;
                case 2:
                    clearScreen();
                    // Taking product ID as input
                    System.out.print("Enter Product ID which you want to add : ");
                    int pId = scan.nextInt();
                    boolean found = false;
                    Product P = null;
                    // Linear search for Product in product list
                    for (Product p : product_list) {
                        if (pId == p.Id) {
                            found = true;
                            P = p;
                            break;
                        }
                    }
                    if (found) {
                        // if Product present then take input the manufacturer ID
                        System.out.print("Enter Manufacturer ID to which you want to add : ");
                        int mId = scan.nextInt();
                        boolean f = false;
                        // Linear search for Manufacturer
                        for (Manufacturer mf : manufacturer_list) {
                            if (mId == mf.Id) {
                                f = true;
                                // Add product to the specified Manufacturer
                                mf.addProduct(P);
                                P.manufacturer = mf;
                                System.out.println("Successfully assigned the product to the manufacturer");
                                break;
                            }
                        }
                        if (!f) {
                            System.out.println("Wrong ID...!!");
                        }
                    } else {
                        // If product not found output the error message
                        System.out.println("Product not found...");
                    }
                    System.out.print("Press Enter to continue...");
                    scan.nextLine();
                    scan.nextLine();
                    break;
                case 3:
                    clearScreen();
                    // Taking input the product ID for adding it to the shop
                    System.out.print("Enter Product ID which you want to add : ");
                    pId = scan.nextInt();
                    found = false;
                    P = null;
                    // Linear search for Product in product list
                    for (Product p : product_list) {
                        if (pId == p.Id) {
                            found = true;
                            P = p;
                            break;
                        }
                    }
                    if (found) {
                        // if found then take input the Shop/Warehouse ID
                        System.out.print("Enter the Shop or Warehouse ID to which you want to add : ");
                        int sId = scan.nextInt();
                        boolean f = false;
                        // Linear shop for Shop/Warehouse
                        for (Shop S : shop_list) {
                            if (sId == S.Id) {
                                f = true;
                                // Add the product with the desired quantity to the Shop
                                Pair pair = new Pair();
                                pair.product = P;
                                System.out.print("Enter the quantity of your prouct : ");
                                pair.quantity = scan.nextInt();
                                S.products.add(pair);
                                System.out.println("Product added to the shop/warehouse successfully...");
                                break;
                            }
                        }
                        if (!f) {
                            System.out.println("Wrong ID...!!");
                        }
                    } else {
                        // If product not present then output the error message
                        System.out.println("Product not found...");
                    }
                    System.out.print("Press Enter to continue...");
                    scan.nextLine();
                    scan.nextLine();
                    break;
                case 4:
                    clearScreen();
                    // Taking input as the Customer ID for placing the order
                    System.out.print("Enter your Customer ID to place order : ");
                    int cId = scan.nextInt();
                    Customer cust = null;
                    // Linear search for Customer in customer list
                    for (Customer C : customer_list) {
                        if (cId == C.Id) {
                            cust = C;
                            break;
                        }
                    }
                    if (cust == null) {
                        System.out.println("Wrong ID...!!");
                    } else {
                        // Taking input of the product which the customer intend to buy
                        System.out.print("Enter the Product ID that you would like to order : ");
                        pId = scan.nextInt();
                        P = null;
                        // Linear search for Product in product list
                        for (Product prod : product_list) {
                            if (prod.Id == pId) {
                                P = prod;
                                break;
                            }
                        }
                        if (P == null) {
                            System.out.println("Wrong ID...!!");
                        } else {
                            // Processing the order
                            System.out.println("Processing your order...");
                            boolean bought = false;
                            int zipcode = cust.zipcode;
                            // searching for shop/warehouse with the same Zipcode as the Customer
                            for (Shop sh : shop_list) {
                                found = false;
                                // Searching for the product in the Shop/Warehouse
                                for (Pair Prod : sh.products) {
                                    if (Prod.product.Id == P.Id) {
                                        found = true;
                                        break;
                                    }
                                }
                                if (sh.zipcode == zipcode && found) {
                                    // if the zipcode of the Shop/Warehouse matches and the product is available in
                                    // the Shop
                                    // then proceed to find the Delivery agent
                                    boolean deliveryAvailable = false;
                                    Delivery person = null;
                                    ArrayList<Delivery> reachableDelivery = new ArrayList<>();
                                    // Linear search for Delivery agent with same zipcode
                                    for (Delivery D : delivery_list) {
                                        if (D.zipcode == zipcode) {
                                            reachableDelivery.add(D);
                                            deliveryAvailable = true;
                                        }
                                    }
                                    int minOrders = Integer.MAX_VALUE;
                                    // finding the Delivery agent with least no. of Deliveries
                                    for (Delivery D : reachableDelivery) {
                                        if (D.numOrders < minOrders) {
                                            minOrders = D.numOrders;
                                            person = D;
                                        }
                                    }
                                    if (deliveryAvailable) {
                                        // If product found then process the order of the Customer providing the
                                        // appropriate information
                                        sh.buyProduct(P);
                                        cust.purchaseProduct(P);
                                        person.incrementOrder();
                                        bought = true;
                                        System.out.println("Successfully processed your order...\n" +
                                                "Details are provided below...\n" +
                                                "Shop : " + sh.name + "(" + sh.Id + ")\n" +
                                                "Delivery Agent : " + person.name + "(" + person.Id + ")");
                                        break;
                                    }
                                }
                            }
                            if (!bought) {
                                // if order was not able to process then output the error message
                                System.out.println(
                                        "Unable to process your order due to non-availability of delivery agency/shop/warehouse");
                            }
                        }
                    }
                    System.out.print("Press Enter to continue...");
                    scan.nextLine();
                    scan.nextLine();
                    break;
                case 5:
                    clearScreen();
                    System.out.print("Enter the Customer ID : ");
                    int id = scan.nextInt();
                    cust = null;
                    for (Customer C : customer_list) {
                        if (C.Id == id) {
                            cust = C;
                            break;
                        }
                    }
                    if (cust == null) {
                        System.out.println("Wrong ID...!!");
                    } else {
                        // print the purchasing history of the customer
                        cust.printPurchases();
                    }
                    System.out.print("Press Enter to continue...");
                    scan.nextLine();
                    scan.nextLine();
                    break;
                case 6:
                    clearScreen();
                    // taking input of shop/warehouse ID whose products you want to see
                    System.out.print("Enter the Shop/Warehouse ID whose products you want ot see : ");
                    id = scan.nextInt();
                    Shop sh = null;
                    // linear searching for shop/warehouse in the shop/warehouse list
                    for (Shop s : shop_list) {
                        if (s.Id == id) {
                            sh = s;
                            break;
                        }
                    }
                    if (sh == null) {
                        System.out.println("Wrong ID...!!");
                    } else {
                        // printing the inventory of the shop/warehouse provided as input
                        sh.printInventory();
                    }
                    System.out.print("Press Enter to continue...");
                    scan.nextLine();
                    scan.nextLine();
                    break;
                case 7:
                    clearScreen();
                    // taking input of manufacturer ID whose products you want to see
                    System.out.println("Enter the Manufacturer ID whose products you want to see : ");
                    id = scan.nextInt();
                    Manufacturer mf = null;
                    // linear searching for manufacturer in manufacturer list
                    for (Manufacturer m : manufacturer_list) {
                        if (m.Id == id) {
                            mf = m;
                            break;
                        }
                    }
                    if (mf == null) {
                        System.out.println("Wrong ID...!!");
                    } else {
                        // printing the products produced by manufacturer in a tabular form
                        mf.printProducts();
                    }
                    System.out.print("Press Enter to continue...");
                    scan.nextLine();
                    scan.nextLine();
                    break;
                case 8:
                    // terminating the program when user chooses the option 8
                    break;
                default:
                    // output an error message if the input is not in the menu
                    System.out.println("You have entered a wrong choice.\nPlease try again...");
                    System.out.print("Press Enter to continue...");
                    scan.nextLine();
                    scan.nextLine();
            }
        } while (input != 8);
        scan.close();// closing the Scanner object
    }

    // Entity class having ID and name as a necessary variable needed for every
    // entity
    static class Entity {
        int Id;
        String name;

        // constructor for taking ID and name as input from user
        public Entity(Scanner scan) {
            System.out.print("Enter ID : ");
            this.Id = scan.nextInt();
            scan.nextLine();
            System.out.print("Enter Name : ");
            this.name = scan.nextLine();
        }
    }

    // All the classes that are following are have inherited the Entity class which
    // is common to all the following classes

    // Manufacturer class
    static class Manufacturer extends Entity {
        // a set of products implemented as a hash map to store products manufactured by
        // manufacturer
        Set<Product> products = new HashSet<Product>();

        // contructor to take manufacturer data as input from user
        public Manufacturer(Scanner scan) {
            super(scan);
        }

        // ultility function for printing the products manufactured by manufacturer in a
        // tabular form
        public void printProducts() {
            System.out.println("The products manufactured by " + this.name + "(" + this.Id + ") are...");
            System.out.printf("%10s\t%20s\t%20s\n", "Sl.No.", "Product ID", "Product Name");
            int i = 1;
            for (Product product : this.products) {
                System.out.printf("%10d\t%20d\t%20s\n", i, product.Id, product.name);
                i++;
            }
        }

        // ultility function for adding a product to the product list of the
        // manufacturer
        public void addProduct(Product product) {
            products.add(product);
        }
    }

    // Customer class
    static class Customer extends Entity {
        // An ArrayList to store the products bought by the customer
        ArrayList<Product> products = new ArrayList<>();
        // int type zipcode
        int zipcode;

        // contructor to take customer data as input from user
        public Customer(Scanner scan) {
            super(scan);
            System.out.print("Enter Zip Code : ");
            this.zipcode = scan.nextInt();
        }

        // ultility function to purchase a product and add it to the product list of the
        // customer
        public void purchaseProduct(Product item) {
            products.add(item);
        }

        // ultility function to print the puchase history of a customer in tabular form
        public void printPurchases() {
            System.out.println("The products purchased by " + this.name + "(" + this.Id + ") are as follows...");
            System.out.printf("%10s\t%20s\t%20s\n", "Sl.No.", "Product Id", "Product Name");
            int i = 1;
            for (Product p : this.products) {
                System.out.printf("%10d\t%20d\t%20s\n", i, p.Id, p.name);
                i++;
            }
        }
    }

    // Product class
    static class Product extends Entity {
        // Manufacturer object to store the manufacturer of the product
        Manufacturer manufacturer = null;

        // contructor to take product data as input from user
        public Product(Scanner scan) {
            super(scan);
        }
    }

    // Shop/Warehouse class
    static class Shop extends Entity {
        // int type zipcode
        int zipcode;
        // ArrayList of type Pair(Product,Quantity) to store the inventory of the
        // Shop/Warehouse
        ArrayList<Pair> products = new ArrayList<>();

        // contructor to take shop/warehouse data as input from user
        public Shop(Scanner scan) {
            super(scan);
            System.out.print("Enter the Zipcode : ");
            this.zipcode = scan.nextInt();
        }

        // ultility function to add a product along with its quantity to the
        // shop/warehouse
        public void addProduct(Product p, int quantity) {
            Pair pair = new Pair();
            pair.product = p;
            pair.quantity = quantity;
            this.products.add(pair);
        }

        // ultility function to buy a product from the shop/warehouse
        public void buyProduct(Product p) {
            Pair pair = new Pair();
            for (Pair P : this.products) {
                if (p.Id == P.product.Id) {
                    pair = P;
                    break;
                }
            }
            pair.quantity--;
            if (pair.quantity == 0) {
                this.products.remove(pair);
            }
        }

        // ultility function to print the Inventory of the shop/warehouse in a tabular
        // format
        public void printInventory() {
            System.out.println("Products available in " + this.name + "(" + this.Id + ") are...");
            System.out.printf("%10s\t%20s\t%20s\t%20s\n", "Sl.No.", "Product ID", "Product Name", "Quantity");
            int i = 1;
            for (Pair p : products) {
                System.out.printf("%10d\t%20d\t%20s\t%20d\n", i, p.product.Id, p.product.name, p.quantity);
                i++;
            }
        }
    }

    // Delivery Agent class
    static class Delivery extends Entity {
        // int type zipcode
        int zipcode;
        // int data to store number of orders performed by the delivery agent
        int numOrders = 0;

        // contructor to take delivery agent data as input from user
        public Delivery(Scanner scan) {
            super(scan);
            System.out.print("Enter the Zipcode : ");
            this.zipcode = scan.nextInt();
        }

        // ultility function to increment the number of orders of a delivery agent
        public void incrementOrder() {
            this.numOrders++;
        }
    }
}