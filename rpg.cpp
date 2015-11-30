#include "rpg.h"
#include "ui_rpg.h"
#include <QDebug>
#include <time.h>
#include <stdlib.h>
#include <QMessageBox>


RPG::RPG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RPG)
{
    ui->setupUi(this);

    connect(ui->lowerCheckBox,SIGNAL(clicked(bool)),this,SLOT(lowerCaseEnabler(bool)));
    connect(ui->upperCheckBox,SIGNAL(clicked(bool)),this,SLOT(upperCaseEnabler(bool)));
    connect(ui->numberCheckBox,SIGNAL(clicked(bool)),this,SLOT(digitEnabler(bool)));
    connect(ui->specialCheckBox,SIGNAL(clicked(bool)),this,SLOT(specialCharacterEnabler(bool)));

    connect(ui->passwordButton,SIGNAL(clicked()),this,SLOT(generatePassword()));

    ui->lengthSpinBox->setValue(20);
    ui->passwordLineEdit->setReadOnly(true);
    setFixedSize(QSize(sizeHint()));

    ui->passwordLineEdit->setStyleSheet(
                "color:rgb(127,0,63);"
                "background-color:rgb(255,255,241);"
                "selection-color:white;"
                "selection-background-color:rgb(191,31,127);"
                "border:2px groove gray;"
                "border-radius:10px;"
                "padding:2px 4px;");


}

RPG::~RPG()
{
    delete ui;
}

void RPG::setVariables()
{
    passwordLength = ui->lengthSpinBox->value();

    if(ui->lowerCheckBox->isChecked())
    {
        if(ui->lowerSpinBoxEnabler->isChecked())
            numOfLowerCaseLetters = ui->lowerSpinBox->value();
        else
            numOfLowerCaseLetters = -1;
    }
    else
        numOfLowerCaseLetters = 0;

    if(ui->upperCheckBox->isChecked())
    {
        if(ui->upperSpinBoxEnabler->isChecked())
            numOfUpperCaseLetters = ui->upperSpinBox->value();
        else
            numOfUpperCaseLetters = -1;
    }
    else
        numOfUpperCaseLetters = 0;

    if(ui->numberCheckBox->isChecked())
    {
        if(ui->numberSpinBoxEnabler->isChecked())
            numOfDigits = ui->numberSpinBox->value();
        else
            numOfDigits = -1;
    }
    else
        numOfDigits = 0;

    if(ui->specialCheckBox->isChecked())
    {
        if(ui->specialSpinBoxEnabler->isChecked())
            numOfSpecialCharacters = ui->specialSpinBox->value();
        else
            numOfSpecialCharacters = -1;
    }
    else
        numOfSpecialCharacters = 0;

}

bool RPG::checkRange()
{
    long int n=0;
    if(numOfLowerCaseLetters!=-1)
        n = numOfLowerCaseLetters;
    if(numOfUpperCaseLetters!=-1)
        n += numOfUpperCaseLetters;
    if(numOfDigits!=-1)
        n += numOfDigits;
    if(numOfSpecialCharacters!=-1)
        n += numOfSpecialCharacters;
    if(n>32767)
    {
        QMessageBox::warning(this,"RPG","Length of password can not be greater than 32767!");
        return true;
    }

    return false;

}


void RPG::lowerCaseEnabler(bool val)
{

    ui->lowerSpinBoxEnabler->setEnabled(val);
    if(!val)
      {
        if(ui->lowerSpinBoxEnabler->isChecked())
            ui->lowerSpinBoxEnabler->setChecked(val);

        if(ui->lowerSpinBox->isEnabled())
           ui->lowerSpinBox->setEnabled(val);

      }
}

void RPG::upperCaseEnabler(bool val)
{

    ui->upperSpinBoxEnabler->setEnabled(val);
    if(!val)
       {
        if(ui->upperSpinBoxEnabler->isChecked())
            ui->upperSpinBoxEnabler->setChecked(val);

        if(ui->upperSpinBox->isEnabled())
           ui->upperSpinBox->setEnabled(val);
       }
}

void RPG::digitEnabler(bool val)
{
    ui->numberSpinBoxEnabler->setEnabled(val);
    if(!val)
    {
        if(ui->numberSpinBoxEnabler->isChecked())
            ui->numberSpinBoxEnabler->setChecked(val);

        if(ui->numberSpinBox->isEnabled())
           ui->numberSpinBox->setEnabled(val);
    }
}

void RPG::specialCharacterEnabler(bool val)
{
    ui->specialSpinBoxEnabler->setEnabled(val);
    if(!val)
       {
        if(ui->specialSpinBoxEnabler->isChecked())
            ui->specialSpinBoxEnabler->setChecked(val);

        if(ui->specialSpinBox->isEnabled())
            ui->specialSpinBox->setEnabled(val);
       }
}


void RPG::generatePassword()
{
   // QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    setVariables();

    if(checkRange())
        return;

    char specialCharacters[31]={'!','@','#','$','%','^','&','*','(',')','-','_','+','=','{','}',
                              '[',']','|','\\',':',';','\'','"',',','.','<','>','?','/'};

    time_t t;
    srand(time(&t));
    int i;
    int total=0;
    char *upperCaseCharacters=0;
    char *lowerCaseCharacters=0;
    char *numbers=0;
    char *special_Characters=0;

    char *password;

    QList<char*> processedCharacters;
    QList<int> autoGenList;


    if(numOfLowerCaseLetters != -1)
    {
        if(numOfLowerCaseLetters)
        {
            lowerCaseCharacters = new char[numOfLowerCaseLetters+1];
            for(i=0;i<numOfLowerCaseLetters;++i)
            {
                lowerCaseCharacters[i] = rand()%26 + 97;
            }
            lowerCaseCharacters[i]='\0';
            total += numOfLowerCaseLetters;
            processedCharacters << lowerCaseCharacters;
        }
    }

    else
    {
        autoGenList << autoGenLowerCaseCharacters;
    }

    if(numOfUpperCaseLetters !=-1)
    {
        if(numOfUpperCaseLetters)
        {
            upperCaseCharacters = new char[numOfUpperCaseLetters+1];
            for(i=0;i<numOfUpperCaseLetters;++i)
            {
              upperCaseCharacters[i] = rand()%26 + 65;
            }

            upperCaseCharacters[i]='\0';
          total += numOfUpperCaseLetters;
          processedCharacters << upperCaseCharacters;
        }
    }
    else
    {
        autoGenList << autoGenUpperCaseCharacters;
    }

    if(numOfDigits != -1)
    {
        if(numOfDigits)
        {
            numbers = new char[numOfDigits+1];
            for(i=0;i<numOfDigits;++i)
            {
                numbers[i] = rand()%10 + 48;
            }
            numbers[i]='\0';
            total += numOfDigits;
            processedCharacters << numbers;
        }
    }
    else
    {
        autoGenList << autoGenNumbers;
    }

    if(numOfSpecialCharacters != -1)
    {
        if(numOfSpecialCharacters)
        {
            special_Characters = new char[numOfSpecialCharacters+1];
            for(i=0;i<numOfSpecialCharacters;++i)
            {
                special_Characters[i] = specialCharacters[rand()%30];
            }
            special_Characters[i]='\0';
            total += numOfSpecialCharacters;
            processedCharacters << special_Characters;
        }
    }

    else
    {
        autoGenList << autoGenSpecialCharacters;
    }


    if(total >= passwordLength || (total<passwordLength && autoGenList.isEmpty()))
    {
        ui->lengthSpinBox->setValue(total);

        for(i=0;i<autoGenList.size();i++)
        {
            switch(autoGenList[i])
            {
             case autoGenLowerCaseCharacters :
                emit
                ui->lowerCheckBox->setChecked(false);
                ui->lowerSpinBoxEnabler->setEnabled(false);
                break;
              case autoGenUpperCaseCharacters:
                ui->upperCheckBox->setChecked(false);
                ui->upperSpinBoxEnabler->setEnabled(false);
                break;
            case autoGenNumbers:
                ui->numberCheckBox->setChecked(false);
                ui->numberSpinBoxEnabler->setEnabled(false);
                break;
            case autoGenSpecialCharacters:
                ui->specialCheckBox->setChecked(false);
                ui->specialSpinBoxEnabler->setEnabled(false);
            }
        }


    }

   else
    {
        int remaining = passwordLength -total;
        int totalRatio=0;
        QList<int> numOfCharcters;
        numOfCharcters << 0 << 0 << 0 << 0;
        for(i=0;i<autoGenList.size() && remaining;i++)
        {
            switch(autoGenList[i])
          {
            case autoGenLowerCaseCharacters :
                 numOfCharcters[0] = 1;
                 totalRatio +=6;
                 break;
            case autoGenUpperCaseCharacters:
                 numOfCharcters[1] = 1;
                 totalRatio +=6;
                 break;
            case autoGenNumbers:
                 numOfCharcters[2] = 1;
                 totalRatio +=3;
                 break;
            case autoGenSpecialCharacters:
                 numOfCharcters[3] = 1;
                 totalRatio +=1;
          }
            remaining--;
        }

        if(remaining)
        {
           int x = remaining / totalRatio;
           int add;
           if(x)
           {
               for(i=0;i<autoGenList.size();++i)
               {
                   switch(autoGenList[i])
                 {
                   case autoGenLowerCaseCharacters :
                        add = x * 6;
                        numOfCharcters[0] += add ;
                        break;
                   case autoGenUpperCaseCharacters:
                        add = x * 6;
                        numOfCharcters[1] += add;
                        break;
                   case autoGenNumbers:
                        add = x * 3;
                        numOfCharcters[2] += add;
                        break;
                   case autoGenSpecialCharacters:
                        add = x * 1;
                        numOfCharcters[3] += add;
                 }
                 remaining = remaining - add;
               }
           }


           while(remaining)
               {
                   for(i=0;i<autoGenList.size()&&remaining;++i)
                   {
                       switch(autoGenList[i])
                     {
                       case autoGenLowerCaseCharacters :
                            numOfCharcters[0]++;
                            break;
                       case autoGenUpperCaseCharacters:
                            numOfCharcters[1]++;
                            break;
                       case autoGenNumbers:
                            numOfCharcters[2]++;
                            break;
                       case autoGenSpecialCharacters:
                            numOfCharcters[3]++;
                     }

                     remaining--;
                  }
              }

        }

        int k;
        for(i=0;i<autoGenList.size();++i)
        {
            switch(autoGenList[i])
            {
            case autoGenLowerCaseCharacters:
             if(numOfCharcters[0])
              {
                lowerCaseCharacters = new char[numOfCharcters[0] + 1];
                for(k=0;k<numOfCharcters[0];k++)
                {
                    lowerCaseCharacters[k] = rand()%26 + 97;
                }
                lowerCaseCharacters[k] = '\0';
                processedCharacters << lowerCaseCharacters;
                total += numOfCharcters[0];
              }
             else
             {
                 ui->lowerCheckBox->setChecked(false);
                 ui->lowerSpinBoxEnabler->setEnabled(false);
             }
                break;

            case autoGenUpperCaseCharacters:
              if(numOfCharcters[1])
              {
                upperCaseCharacters = new char[numOfCharcters[1] + 1];
                for(k=0;k<numOfCharcters[1];k++)
                {
                    upperCaseCharacters[k] = rand()%26 + 65;
                }
                upperCaseCharacters[k] = '\0';
                processedCharacters << upperCaseCharacters;
                total += numOfCharcters[1];
              }
              else
              {
                  ui->upperCheckBox->setChecked(false);
                  ui->upperSpinBoxEnabler->setEnabled(false);
              }
                break;

            case autoGenNumbers:
                if(numOfCharcters[2])
                {
                    numbers = new char[numOfCharcters[2] + 1];
                    for(k=0;k<numOfCharcters[2];k++)
                    {
                        numbers[k] = rand()%10 + 48;
                    }
                    numbers[k] = '\0';
                    processedCharacters << numbers;
                    total += numOfCharcters[2];
                }
                else
                {
                    ui->numberCheckBox->setChecked(false);
                    ui->numberSpinBoxEnabler->setEnabled(false);
                }
                break;

            case autoGenSpecialCharacters:
                if(numOfCharcters[3])
                {
                    special_Characters = new char[numOfCharcters[3] + 1];
                    for(k=0;k<numOfCharcters[3];k++)
                    {
                        special_Characters[k] = specialCharacters[rand()%30];
                    }
                    special_Characters[k] = '\0';
                    processedCharacters << special_Characters;
                    total += numOfCharcters[3];
                }
                else
                {
                    ui->specialCheckBox->setChecked(false);
                    ui->specialSpinBoxEnabler->setEnabled(false);
                }
                    break;

            }
        }

        Q_ASSERT(total == passwordLength);
    }

    int numOfTypes = processedCharacters.size();
    QList<int> sizeOfType;

    for(i=0;i<numOfTypes;++i)
        sizeOfType << strlen(processedCharacters[i]);


    password = new char[total+1];

    QList<int> l;
    l << 0 << 0 << 0 << 0;
    int j;
    int *order;
    order = new int[total];

  if(total<=1000)
  {
    for(i=0;i<total;i++)
        order[i]=-1;
    int flag;
    i=0;
    int p;
    while(i<total)
    {
        j=rand()%total;
        flag=1;
        for(p=0;p<=i;p++)
        {
            if(order[p]==j)
            {
                flag=0;
                break;
            }
        }
        if(flag)
        {
            order[i]=j;
            i++;
        }
    }
  }

  else
  {
      for(i=0;i<total;i++)
          order[i]=i;
  }

  for(i=0;i<total;)
    {
     j=rand()%numOfTypes;

      if(l[j] < sizeOfType[j])
        {
        password[order[i]] = processedCharacters[j][l[j]];
            l[j]++;
            i++;
        }
        else
        {
            processedCharacters.removeAt(j);
            l.removeAt(j);
            sizeOfType.removeAt(j);
            numOfTypes--;
        }

    }
    password[total]='\0';

    ui->passwordLineEdit->setText(password);


   // QApplication::restoreOverrideCursor();

    delete lowerCaseCharacters;
    delete upperCaseCharacters;
    delete numbers;
    delete special_Characters;
    delete password;
    delete order;
}



