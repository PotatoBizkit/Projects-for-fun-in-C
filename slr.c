#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

typedef struct salary
{
    int index;
    float exp;
    int salary;
} sa;

int main(){
    int count=0, col1, col3;
    float col2;
    char t[100];

    FILE *f = NULL;
    f = fopen("Salary_dataset.csv", "r");

    while (fgets(t, sizeof(t), f))
    {
        count++;
    }
    
    rewind(f);
    printf("%d\n\n", count);

    sa s[count-1];

    fgets(t, sizeof(t), f);

    for (int i = 0; i < count-1; i++)
    {
        fgets(t, sizeof(t), f);
        sscanf(t, "%d,%f,%d", &col1, &col2, &col3);
        s[i].index = col1;
        s[i].exp = col2;
        s[i].salary = col3;
        printf("%d, %f, %d\n", col1, col2, col3);
    }
    
    fclose(f);

    srand(69);

    for (int i = count-2; i > 0; i--)
    {
        int j = rand() % (i+1);

        sa temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }

    int tts = ((count-1)*80)/100;
    int Y_train[tts], Y_test[count-1-tts];
    float X_train[tts], X_test[count-1-tts];

    for (int i = 0; i < tts; i++)
    {
        X_train[i] = s[i].exp;
        Y_train[i] = s[i].salary;
    }

    for (int i = 0; i < count-1-tts; i++)
    {
        X_test[i] = s[tts+i].exp;
        Y_test[i] = s[tts+i].salary;
    }

    float mse, r2, rmse, Y_test_mean, X_train_mean, Y_train_mean, num1=0, num2=0, den=0, slope, intercept, Y_pred[count-1-tts]; 

    for (int i = 0; i < tts; i++)
    {
        num1 += X_train[i];
        num2 += Y_train[i];
    }
    
    X_train_mean = num1/tts;
    Y_train_mean = num2/tts;

    printf("\nx mean = %f\ny mean = %f\n", X_train_mean, Y_train_mean);

    num1 = 0;
    for (int i = 0; i < tts; i++)
    {
        num1 += (Y_train[i]-Y_train_mean)*(X_train[i]-X_train_mean);
        den += (X_train[i]-X_train_mean)*(X_train[i]-X_train_mean);
    }

    slope = num1/den;
    intercept = Y_train_mean - (slope*X_train_mean);
    printf("\nslope = %f\nintercept = %f\n", slope, intercept);

    printf("\nPredicted := Actual\n");
    for (int i = 0; i < count-1-tts; i++)
    {
        Y_pred[i] = (slope*X_test[i]) + intercept;
        printf("%f := %d\n", Y_pred[i], Y_test[i]);
    }

    num1 = 0;
    for (int i = 0; i < count-1-tts; i++)
    {
        num1 += Y_test[i];
    }
    Y_test_mean = num1/(count-1-tts);
    
    num1 = 0;
    num2 = 0;
    for (int i = 0; i < count-1-tts; i++)
    {
        num1 += (Y_pred[i]-Y_test[i])*(Y_pred[i]-Y_test[i]);
        num2 += (Y_test[i]-Y_test_mean)*(Y_test[i]-Y_test_mean);
    }

    mse = num1/(count-1-tts);
    r2 = 1 - (num1/num2);
    rmse = sqrt(mse);
    printf("\nMSE = %f\nR2 score = %f\nRMSE = %f\n", mse, r2, rmse);

    return 0;
}