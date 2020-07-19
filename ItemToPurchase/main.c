#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

int main(void) {
 
   ItemToPurchase  item1;
   ItemToPurchase  item2;
   // MakeItemBlank(item1);
   MakeItemBlank(&item1);
   // MakeItemBlank(item2);
   MakeItemBlank(&item2);
   char name[59];
   int price;
   int quantity;
   
   printf("Item 1\n");
   printf("Enter the item name:\n");
   char c = getchar();
   int j = 0;
   while(c != '\n' && c != EOF) 
   {
      name[j] = c;
      j++;
      c = getchar();
   }
   name[j] = '\0';
   strcpy(item1.itemName, name);
   printf("Enter the item price:\n");
   scanf("%d ", &price);
   item1.itemPrice = price;
   printf("Enter the item quantity:\n");
   scanf("%d ", &quantity);
   item1.itemQuantity = quantity;
   
   
   printf("\nItem 2\n");
   printf("Enter the item name:\n");
   c = getchar();
   j = 0;
   while(c != '\n' && c != EOF) 
   {
      name[j] = c;
      j++;
      c = getchar();
   }
   name[j] = '\0';
   strcpy(item2.itemName, name);
   printf("Enter the item price:\n");
   scanf("%d ", &price);
   item2.itemPrice = price;
   printf("Enter the item quantity:\n");
   scanf("%d ", &quantity);
   item2.itemQuantity = quantity;
   
   
   printf("\nTOTAL COST\n");
   PrintItemCost(item1);
   PrintItemCost(item2);
   printf("\nTotal: $%d\n", item1.itemPrice * item1.itemQuantity + item2.itemPrice * item2.itemQuantity);
   
   return 0;
}

