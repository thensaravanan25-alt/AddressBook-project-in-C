#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    int choice , i, j;
    Contact temp;
     int size= addressBook->contactCount;
     printf("\n1.Sort by name : ");
     printf("\n2.Sort by phone number : ");
     printf("\n3. Sort by email :");
     printf("\nEnter your choice : ");
     scanf("%d",&choice);
     getchar();
     switch(choice)
     {
        case 1:
               for(i=0;i<size-1;i++)
               {
                 for(j=0;j<size-i-1;j++)
                 {
                    if(strcmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name)>0)
                    {
                       temp= addressBook->contacts[j];
                       addressBook->contacts[j]= addressBook->contacts[j+1];
                       addressBook->contacts[j+1]=temp;
                    }
                 }
               }
     
         break;
         case 2:
            for(i=0;i<size-1;i++)
               {
                 for(j=0;j<size-i-1;j++)
                 {
                    if(strcmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone)>0)
                    {
                       temp= addressBook->contacts[j];
                       addressBook->contacts[j]= addressBook->contacts[j+1];
                       addressBook->contacts[j+1]=temp;
                    }
                 }
               }
         break;
         case 3:
                 for(i=0;i<size-1;i++)
               {
                 for(j=0;j<size-i-1;j++)
                 {
                    if(strcmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email)>0)
                    {
                       temp= addressBook->contacts[j];
                       addressBook->contacts[j]= addressBook->contacts[j+1];
                       addressBook->contacts[j+1]=temp;
                    }
                 }
               }
          break;
    }
     for(i=0;i<size;i++)
     {
        printf("%s  %s  %s\n",addressBook->contacts[i].name , addressBook->contacts[i].phone,addressBook->contacts[i].email);
     }
    
    // Sort contacts based on the chosen criteria
    
}

void initialize(AddressBook *addressBook) {
    //addressBook->contactCount = 0;
    //populateAddressBook(addressBook); // functional call 
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
int check_phonenumber(AddressBook *addressBook , char *phone)
{
    int i;
    for(i=0;i< addressBook-> contactCount;i++)
    {
        if (strcmp (phone , addressBook -> contacts[i].phone) ==0)
        {
            return 0;
        }
    }
    return 1;
}
int  check_email(AddressBook *addressBook , char *email)
{
    int i;
    for(i=0;i<addressBook-> contactCount;i++)
    {
        if(strcmp( addressBook-> contacts[i].email , email)==0)
        {
            return 0;
        }
    }
    return 1;

}

void createContact(AddressBook *addressBook) // creating a new contact 
{
    char name[30] , phone[50], email[50];
    int length=0;
    //char substr[4]= ".com" ;
    getchar();
    printf("Enter new name : ");
    scanf(" %[^\n]",name);
    getchar();
    do{

        printf("Enter the phone number : ");
        scanf("%s",phone);
        length=strlen(phone);  // checking phone number length
        getchar();
     }while(length != 10);

 
    do{
        printf("Enteer the email : ");    //checking email
        scanf("%s" , email);
        if((strchr(email , '@')==NULL )|| (strstr(email , ".com")==NULL))
        {
            printf("INVALID EMAIL TRY AGAIN \n");
        }
    }while((strchr(email , '@')==NULL )|| (strstr(email , ".com")==NULL));
    
 
    if (check_phonenumber(addressBook ,phone)==0)// function calling
    {
        printf("Then phone number is already exist !\n");  //check the number is already exixts or not
        printf("Enter the  phone number again : ");
        scanf("%s", phone);
    }
    else
       {
            strcpy(addressBook->contacts[addressBook->contactCount].name, name);
             strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
             strcpy(addressBook->contacts[addressBook->contactCount].email, email);
            (addressBook->contactCount)++;
       }
            

     
   if(check_email(addressBook , email)==0) // check the email is already exixts or not
   {
      printf("The email already exixt !\n");
      printf("Enter the email again : ");
      scanf("%s", email);
     
   }
   else
   {
           strcpy(addressBook->contacts[addressBook->contactCount].name, name);
           strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
           strcpy(addressBook->contacts[addressBook->contactCount].email, email);
            (addressBook->contactCount)++;
   }
}
    /* Define the logic to create a Contacts */


void searchContact(AddressBook *addressBook)  // search the contacts by name number and email
{
    int choice;
    int i;
    int flag =0;
    char name[60]; 
    char phone_number[50];
    char email[50];
    printf("\n1.Search by name  : ");
    printf("\n2.search by phone : ");
    printf("\n3.search by email : ");
    printf("\nEnter the choice: ");
    scanf("%d",&choice);
    getchar();
    switch(choice)
    {
        case 1:
           printf("\nEnter the name : ");
           scanf("%[^\n]", name);
           for( i=0;i < addressBook->contactCount;i++ )
           {
              if((strcmp(name , addressBook-> contacts[i].name)) ==0)
              {
                printf("%s   %s   %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);
                   flag =1;
                   break;
              }
           }
           if(flag ==0)
           {
            printf(" Contact not found in my addressbok.\n");
           }
           
        break;
        case 2:
        printf("\nEnter the phone number :");
        scanf("%[^\n]",phone_number);
        for(i=0;i< addressBook-> contactCount;i++)
        {
            if(strcmp(phone_number, addressBook->contacts[i].phone)==0)
            {
                printf("%s  %s  %s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);
                flag =1;
                break;
            }
        }
        if(flag==0)
        {
            printf("Contact not found in that addressbook\n");
        }
        break;
        case 3:
           printf("\nEnter email id to search :");
           scanf("%[^\n]",email);
           for(i=0;i< addressBook->contactCount;i++)
           {
              if(strcmp(email, addressBook->contacts[i].email)==0)
              {
                printf("%s  %s  %s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);
                flag=1;
                break;
              }
           }
           if(flag==0)
           {
              printf("Contact not found in that address book\n");
           }
        break;
        default :
         printf("\n Please Enter valid number(1-3).");
        break;
    }

    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)   // edit the contacts
{
    char name[50], phone[50], email[50];
    int index ,i;
    printf("Select the contact\n");
    printf("\n 1. Search  name to edit : ");
    printf("\n 2. Search  phone number to edit :");
    printf("\n 3. Search email to edit : ");
    int option , flag=0;
    printf("\n Enter the choice : ");
    scanf("%d",&option);
    switch(option)
    {
        case 1:
        do{
              printf("Enter the name : "); 
              getchar();
              scanf("%[^\n]",name);
              
              for( i=0;i < addressBook->contactCount;i++ )
              {
                  if((strcmp(name , addressBook-> contacts[i].name)) ==0)
                  { 
                        index=i;
                        flag =1;
                        break;
                  }
              }
              if (flag==0)
              printf("The name is not present in the addressbook ! Reneter the name\n");
        }while(flag ==0);

        break;
        case 2:
           
        do{
              printf("Enter the phone number : ");
              getchar();
              scanf("%s", phone);
              
              for( i=0;i < addressBook->contactCount;i++ )
              {
                  if((strcmp(phone , addressBook-> contacts[i].phone)) ==0)
                  { 
                        index=i;
                        flag =1;
                        break;
                  }
              }
              if (flag==0)
              printf("The phone number  is not present in the addressbook ! Reneter the number\n");
        }while(flag ==0);

        break;
        case 3:
        do{
           printf("Enter the email : ");
              getchar();
              scanf("%s", email);
              
              for( i=0;i < addressBook->contactCount;i++ )
              {
                  if((strcmp(email , addressBook-> contacts[i].email)) ==0)
                  { 
                        index=i;
                        flag =1;
                        break;
                  }
              }
              if (flag==0)
              printf("The email  is not present in the addressbook ! Reneter the email\n");
        }while(flag ==0);

         break;
        
    }
    printf("\n 1. Edit the name : ");
    printf("\n 2. Edit the phone number :");
    printf("\n 3. Edit the e mail : ");
    printf("\nEnter the option : ");
    scanf("%d", &option);
    switch(option)
    {
        case 1:    //edit the name 
           printf("Enter the new name : ");
           getchar();
           scanf("%[^\n]", name);
           strcpy(addressBook->contacts[index].name ,name );
           break;

        case 2:   // edit the number
          printf("Enter the new phone number : ");
          getchar();
          scanf("%s", phone );
          strcpy(addressBook->contacts[index].phone, phone);
          break;
        case 3:  // edit the email
            printf("Enter the new email : ");
            getchar();
            scanf("%s", email);
            strcpy(addressBook->contacts[index].email , email);
            break;  

    }
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)   // delete the contacts
{
    char name[50], email[50],phone[50];
    int index , i ,option, flag =0;
    printf("\n1.  Search by name to delete : ");
    printf("\n 2. Search by number to delete   : ");
    printf("\n 3.  search  by email to delete : ");
    printf("\n Enter the option: ");
    scanf("%d", &option);
    switch(option)
    {
        case 1:
        do{
             printf("Enter the name to delete: ");    //search name to delete
             getchar();
             scanf("%[^\n]", name);
             for(i=0;i< addressBook->contactCount;i++)
             {
                if(strcmp(addressBook->contacts[i].name , name)==0)
                {
                    index=i;
                    flag=1;
                    break;
                     
                }
            }
            if(flag ==0)
            printf("Entered name is not present ! Please renter the name \n");
        }while(flag ==0);
        if(flag ==1)
        {
            for(i=index;i< addressBook->contactCount;i++)
            {
             addressBook->contacts[i] = addressBook->contacts[i+1];
            }
              (addressBook-> contactCount)--;
        }
         break;
        case 2:
        do{
               printf("Enter the number to delete : ");  //search number to delete
               scanf("%s",phone);
               for(i=0;i<addressBook->contactCount;i++)
               {
                  if(strcmp(addressBook->contacts[i].phone, phone)==0)
                  {
                    index=i;
                    flag =1;
                    break;

                  }
               }
               if(flag ==0)
               printf("Entered phone number is not present ! Please renetr it \n");
             } while(flag==0);
             if(flag ==1)
             {
                for(i=index;i<addressBook->contactCount;i++)
                {  
                   addressBook->contacts[i]= addressBook->contacts[i+1];
                }
                   (addressBook->contactCount)--;
                
             }
               
               break;
         case 3:
         do{
               printf("Enter the email to delete : ");  // search email to delete
               scanf("%s",email);
               for(i=0;i<addressBook->contactCount;i++)
               {
                if(strcmp(addressBook->contacts[i].email , email)==0)
                {
                    flag =1;
                    index=i;
                    break;
                }
               }
               if(flag ==0)
               printf("Entered email is not present please reenter it \n");
         }while(flag ==0);
         if(flag ==1)
         {
            for(i=index;i<addressBook->contactCount;i++)
            {
               addressBook->contacts[i]=addressBook->contacts[i+1];
            }
               (addressBook->contactCount)--;
         }
               break;      
   }
/* Define the logic for deletecontact */
}
