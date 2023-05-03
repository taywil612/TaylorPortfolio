An electronic company specializes in manufacturing devices such as smartphones, tablet, laptops, and smartwatches (4 factories for the abstract factory pattern, 
3 main products). Each device has different components. Suppose you are writing a program to test the components of the devices. The components we are interested in 
are displays, batteries, and processors (the 3 products, per one factory each product relates to the 4 factories ex. Display is produced 4 times for each factory). 
These components are different in different device. Each device has its own program for testing these components. To know which test to run, you will need to instantiate
objects that correspond to each one of the components. (around 20 classes for the UML diagram)

We assume that device to be tested are stored in a configuration file (text file). Because this situation fits the Abstract Factory pattern so well, you can use that 
pattern to organize the creation of objects that correspond to each device. You will also need to use the variation of singleton pattern to ensure that at most two 
instances of each device in each test run. Please note finishing running all devices specified in the configuration file is considered as one test run. 

Here is an example of the configuration file content.
Smartphone
Smartwatch
Laptop
Smartwatch
Laptop
Tablet
Laptop
Smartwatch
Smartphone
Tablet

