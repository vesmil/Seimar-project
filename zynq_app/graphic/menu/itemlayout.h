#ifndef ITEMLAYOUT_H
#define ITEMLAYOUT_H

#include <QHBoxLayout>

//! \brief custom layout for item in a list - so all have unified look
class ItemLayout : public QHBoxLayout
{
    Q_OBJECT

public:
    ItemLayout(QWidget *parent);
};

#endif // ITEMLAYOUT_H
