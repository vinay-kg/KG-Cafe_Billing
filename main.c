#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
    char item[20];
    float price;
    int qty;
};
struct orders{
    char customer[50];
    char date[50];
    int numofItems;
    struct items itm[50];
};

void BillBana(char name[50],char date[30]){
    printf("\n\n");
    printf("\t\t\t\t\tKG Cafe\t\t\t\t\t\t");
    printf("\n-------------------------------------------------------------------------------------------");
    printf("\nDate: %s",date);
    printf("\nInvoice to: %s ",name);
    printf("\n");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("Items\t\t");
    printf("Quantity\t\t");
    printf("Total\t\t");
    printf("\n-------------------------------------------------------------------------------------------\n");
    printf("\n");

}
void Kaise_Banau_Bill(char item[20],int qty,float price){
    printf("%s\t\t",item);
    printf("   %d\t\t",qty);
    printf("        %.2f\t\t",qty*price);
    printf("\n");
}

void Dekh_Bill(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal = total-dis;
    float gst = 0.18*netTotal;
    float grandTotal = netTotal + gst;
    printf("------------------------------------------------------------------------------------------\n");
    printf("\nSub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%\t\t\t%.2f",dis);
    printf("\n\t\t\t\t--------------------------------------------------------------------------------\n");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nGST @18%\t\t\t\t%.2f",gst);
    printf("\n\t\t\t\t--------------------------------------------------------------------------------\n");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n\t\t\t\t--------------------------------------------------------------------------------\n");

}

int main(){
    int opt,n;
    char name[50];
    char saveBill = 'y',flag='y';
    FILE *fp;
    while(flag == 'y') {
        float total;
        int i =0;
        struct orders ord;
        struct orders order;
        printf("===========================================KG CAFE==============================================");

        printf("\n1.Generate Invoice");
        printf("\n2.Show all Invoices");
        printf("\n3.Search Invoices");
        printf("\n4.Exit");

        printf("\n\nYour Choice:");
        scanf("%d", &opt);

        printf("\nYour Choice is %d", opt);
        printf("\n");

        switch (opt) {
            case 1:

                printf("\nPlease Enter the Name of Customer:\t");
                fgetc(stdin);
                fgets(ord.customer, 50, stdin);
                ord.customer[strlen(ord.customer) - 1] = 0;
                strcpy(ord.date, __DATE__);
                printf("\nPlease Enter the number of items:\t");
                scanf("%d", &n);
                ord.numofItems = n;

                for (int i = 0; i < n; i++) {
                    fgetc(stdin);
                    printf("\n\n");
                    printf("\nPlease Enter the item %d:\t", i + 1);
                    fgets(ord.itm[i].item, 20, stdin);
                    ord.itm[i].item[strlen(ord.itm[i].item) - 1] = '\0';
                    printf("\nPlease Enter the quantity:\t");
                    scanf("%d", &ord.itm[i].qty);
                    printf("\nPlease Enter the unit price:\t");
                    scanf("%f", &ord.itm[i].price);
                    total += ord.itm[i].qty * ord.itm[i].price;
                }

                BillBana(ord.customer, ord.date);

                for (int i = 0; i < ord.numofItems; i++) {
                    Kaise_Banau_Bill(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                }
                Dekh_Bill(total);
                printf("\nDo you want to save your invoice [y/n]:\t");
                scanf("%s", &saveBill);
                if (saveBill == 'y') {
                    fp = fopen("KGCAFE.txt", "a+");
                    fwrite(&ord, sizeof(struct orders), 1, fp);
                    if (fwrite != 0) {
                        printf("\nSaved Successfully");
                    } else
                        printf("\nError Saving");
                    fclose(fp);
                }
                break;

            case 2:
                fp = fopen("KGCafe.txt", "r");
                printf("\n**********************Previous  Invoices************************\n");
                while (fread(&order, sizeof(struct orders), 1, fp)) {
                    float tot = 0;
                    BillBana(order.customer, order.date);
                    for (int i = 0; i < order.numofItems; i++) {
                        Kaise_Banau_Bill(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    Dekh_Bill(tot);

                }
                fclose(fp);
                break;

            case 3:
                printf("\nEnter the name of customer:\t");
                fgetc(stdin);
                fgets(name,50,stdin);
                name[strlen(name) - 1] ='\0';

                fp = fopen("KGCafe.txt", "r");
                printf("\n**********************Invoice of %s************************\n", name);
                while (fread(&order, sizeof(struct orders), 1, fp)) {
                    float tot = 0;
                    if (!strcmp(order.customer, name)) {
                        BillBana(order.customer, order.date);
                        for (int j = 0; j < order.numofItems; j++) {
                            Kaise_Banau_Bill(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                            tot += order.itm[i].qty * order.itm[i].price;
                        }
                        Dekh_Bill(tot);
                        i = 1;
                    }
                    fclose(fp);

                }
                if (!i) {
                    printf("\nNahi mila tera koi invoice");
                }
                fclose(fp);
                break;

            case 4:
                printf("\n\t Chal Nikal");
                exit(0);
                break;

            default:
                printf("\nKuch Bhi Matlab");
                break;

        }
        printf("\n Aur Kuch Sir?[y/n]\t");
        scanf("%s",&flag);
    }
    printf("\n\n");
    return 0;

    }

