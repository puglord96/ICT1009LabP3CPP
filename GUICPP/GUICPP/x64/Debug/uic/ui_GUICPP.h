/********************************************************************************
** Form generated from reading UI file 'GUICPP.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUICPP_H
#define UI_GUICPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUICPPClass
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *redditTab;
    QGridLayout *gridLayout_2;
    QTableWidget *redditTableWidget;
    QWidget *twitterTab;
    QGridLayout *gridLayout_3;
    QTableWidget *twittertableWidget;

    void setupUi(QWidget *GUICPPClass)
    {
        if (GUICPPClass->objectName().isEmpty())
            GUICPPClass->setObjectName(QString::fromUtf8("GUICPPClass"));
        GUICPPClass->resize(1269, 892);
        gridLayout = new QGridLayout(GUICPPClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(GUICPPClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMaximumSize(QSize(1261, 861));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        redditTab = new QWidget();
        redditTab->setObjectName(QString::fromUtf8("redditTab"));
        gridLayout_2 = new QGridLayout(redditTab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        redditTableWidget = new QTableWidget(redditTab);
        if (redditTableWidget->columnCount() < 6)
            redditTableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        redditTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        redditTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        redditTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        redditTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        redditTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        redditTableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        redditTableWidget->setObjectName(QString::fromUtf8("redditTableWidget"));

        gridLayout_2->addWidget(redditTableWidget, 0, 0, 1, 1);

        tabWidget->addTab(redditTab, QString());
        twitterTab = new QWidget();
        twitterTab->setObjectName(QString::fromUtf8("twitterTab"));
        gridLayout_3 = new QGridLayout(twitterTab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        twittertableWidget = new QTableWidget(twitterTab);
        if (twittertableWidget->columnCount() < 5)
            twittertableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        twittertableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        twittertableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        twittertableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        twittertableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        twittertableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        twittertableWidget->setObjectName(QString::fromUtf8("twittertableWidget"));

        gridLayout_3->addWidget(twittertableWidget, 0, 0, 1, 1);

        tabWidget->addTab(twitterTab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(GUICPPClass);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(GUICPPClass);
    } // setupUi

    void retranslateUi(QWidget *GUICPPClass)
    {
        GUICPPClass->setWindowTitle(QCoreApplication::translate("GUICPPClass", "GUICPP", nullptr));
        QTableWidgetItem *___qtablewidgetitem = redditTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GUICPPClass", "Title", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = redditTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("GUICPPClass", "Likes", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = redditTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("GUICPPClass", "Username", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = redditTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("GUICPPClass", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = redditTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("GUICPPClass", "Subreddit", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = redditTableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("GUICPPClass", "Link", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(redditTab), QCoreApplication::translate("GUICPPClass", "Reddit", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = twittertableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("GUICPPClass", "Tweet", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = twittertableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("GUICPPClass", "Favourites", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = twittertableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("GUICPPClass", "Username", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = twittertableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("GUICPPClass", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = twittertableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("GUICPPClass", "Retweets", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(twitterTab), QCoreApplication::translate("GUICPPClass", "Twitter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUICPPClass: public Ui_GUICPPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUICPP_H
