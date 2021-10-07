# Inventory

This project employs the idea of the abstract data type String, using this abstract data type a command of either "inventory", "purchase", or "summarize" which is parsed
from the instruction set, then it is up to the three functions to recognize what the function is, read the name of the person, and update the customer's number of items and 
inventory of the store's items after the instruction is done. Summarize should say a basic summary of what the store's inventory is.

processInventory function reads the item type and quantity from the input file and update the store’s inventory of the indicated item type.

processPurchase function should read the customer’s name, the item type and the quantity. The function should look up the customer in the customer database.
(creating a new customer record if this is a 1st-time customer) and increment the number of items purchased by this customer in their customer record. 

processSummarize() – This command should print out a summary. The summary should first display the number of Bottles, Rattles, and Diapers remaining in inventory 
at the time of the Summarize command. Next, the summary should display how many different customers have come to the store for purchases. Finally, the summary should 
report which customer purchased the most diapers (and how many diapers), who purchased the most bottles (and how many) and who purchased the most rattles (and 
how many). If a certain item has not been purchased by anybody, then the summary should indicate that.
