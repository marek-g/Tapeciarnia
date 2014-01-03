#ifndef TAPECIARNIAQMLWINDOW_H
#define TAPECIARNIAQMLWINDOW_H

#include <QQuickView>

class TapeciarniaQMLWindow : public QQuickView
{
    Q_OBJECT

signals:

    void windowClosing();

protected:

    bool event(QEvent *event)
    {
        switch (event->type())
        {
            case QEvent::Close:
                emit windowClosing();
            break;

            default: break;
        }

        return QQuickView::event(event);
    }
};

#endif // TAPECIARNIAQMLWINDOW_H
