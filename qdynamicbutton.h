#ifndef QDYNAMICBUTTON_H
#define QDYNAMICBUTTON_H

#include <QPushButton>

class QDynamicButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QDynamicButton(std::string nam,QWidget *parent = 0);
    ~QDynamicButton();
    static int ResID;   // A static variable counter buttons rooms
    int getID();        // Function to return a local number buttons

    std::string getName(){return name; };
public slots:

private:
    int buttonID = 0;// Local variable number of the button
    std::string name;
};

#endif // QDYNAMICBUTTON_H
