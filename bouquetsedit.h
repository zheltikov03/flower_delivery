#ifndef BOUQUETSEDIT_H
#define BOUQUETSEDIT_H

#include <QDialog>

namespace Ui {
class bouquetsEdit;
}

class bouquetsEdit : public QDialog
{
    Q_OBJECT

public:
    explicit bouquetsEdit(QWidget *parent = nullptr);
    ~bouquetsEdit();

private:
    Ui::bouquetsEdit *ui;
};

#endif // BOUQUETSEDIT_H
