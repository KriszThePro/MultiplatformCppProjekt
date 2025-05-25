#include "appstyle.h"
#include <QPalette>

void Ui::setupAppStyle(QApplication *app) {
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    app->setPalette(darkPalette);

    QString darkStyle = R"(
        QMenuBar {
            background-color: #353535;
            color: white;
            border-bottom: 1px solid #2c2c2c;
        }
        QMenuBar::item {
            background: transparent;
        }
        QMenuBar::item:selected {
            background: #3c3c3c;
        }

        QMenu {
            background-color: #353535;
            color: white;
            border: 1px solid #2c2c2c;
        }
        QMenu::item:selected {
            background-color: #3c3c3c;
        }
    )";
    app->setStyleSheet(darkStyle);
}
