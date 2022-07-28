#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 单选按钮设置默认值
    ui->btn_man->setChecked(true);
    // 获取单选按钮状态
    connect(ui->btn_woman, &QRadioButton::clicked, this, [=]()
            { qDebug() << "选中了女"; });

    // 获取复选按钮状态
    connect(ui->checkBox_1, &QCheckBox::stateChanged, this, [=](int state)
            { qDebug() << state; });

    // ListWidget
    QListWidgetItem *item = new QListWidgetItem("静夜思");
    QListWidgetItem *item1 = new QListWidgetItem("[唐] 李白");
    // 在ListWidget中添加子项
    ui->listWidget->addItem(item);
    ui->listWidget->addItem(item1);
    // 设置文本对齐方式
    item->setTextAlignment(Qt::AlignHCenter);
    item1->setTextAlignment(Qt::AlignHCenter);

    // 在ListWidget中添加子项
    QStringList list;
    list.append("床前明月光");
    list.append("疑是地上霜");
    list.append("举头望明月");
    list.append("低头思故乡");
    ui->listWidget->addItems(list);

    // TreeWidget
    // 设置头部信息
    ui->treeWidget->setHeaderLabels(QStringList() << "英雄"
                                                  << "英雄简介");
    // 添加父项
    QTreeWidgetItem *warrior = new QTreeWidgetItem(QStringList() << "战士");
    QTreeWidgetItem *rabbi = new QTreeWidgetItem(QStringList() << "法师");
    QTreeWidgetItem *shooter = new QTreeWidgetItem(QStringList() << "射手");
    ui->treeWidget->addTopLevelItem(warrior);
    ui->treeWidget->addTopLevelItem(rabbi);
    ui->treeWidget->addTopLevelItem(shooter);
    // 添加子项
    QTreeWidgetItem *warrior1 = new QTreeWidgetItem(QStringList() << "剑魔"
                                                                  << "亚托克斯");
    warrior->addChild(warrior1);
    QTreeWidgetItem *rabbi1 = new QTreeWidgetItem(QStringList() << "小鱼人"
                                                                << "潮汐海灵");
    rabbi->addChild(rabbi1);
    QTreeWidgetItem *shooter1 = new QTreeWidgetItem(QStringList() << "金克斯"
                                                                  << "暴走萝莉");
    shooter->addChild(shooter1);
    warrior->textAlignment(2);

    // TableWidget
    // 设置列数
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "id"
                                                             << "name"
                                                             << "age");
    // 设置行数
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setItem(4, 0, new QTableWidgetItem(QString("12345")));
    ui->tableWidget->setItem(4, 1, new QTableWidgetItem(QString("张三")));
    ui->tableWidget->setItem(4, 2, new QTableWidgetItem(QString("18")));

    QList<QString> idList;
    idList << "1"
           << "2"
           << "3"
           << "4";
    QStringList nameList;
    nameList.append("李四");
    nameList.append("王五");
    nameList.append("赵六");
    nameList.append("陈七");

    for (int i = 0; i < 4; i++)
    {
        int col = 0;
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(idList[i]));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(nameList.at(i)));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(QString::number(i + 18)));
    }
}

Widget::~Widget()
{
    delete ui;
}
