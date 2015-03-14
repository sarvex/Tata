#include "IpValidator.h"

#include <QDebug>
#include <QStringList>


IpValidator::IpValidator() {
}

void IpValidator::fixup(QString& input) const {
        QStringList list = input.split(".");

        bool integer;

        for (int index = 0; index < list.size(); index++) {
            list[index].toInt(&integer);

            if (!integer) {
                // replace non-integers with a zero value
                list[index] = "0";
            }/* else {
                // force right align
                list[index].remove(" ");
                list[index] = list[index].rightJustified(3,' ');
            }*/
        }

        for ( int index = list.size (); index < 4; index++ ) {
            list.append ("0");
        }

        input = list.join(".");
}

QValidator::State IpValidator::validate(QString& input, int& position) const {
    Q_UNUSED(position)

    if (input.isEmpty())  {
        return Invalid;
    }

    QStringList list = input.split(".");

    if ( 4 < list.size()) {
        return Invalid;
    }

    bool emptyGroup = false;
    bool integer;

    for (int index = 0; index <list.size (); index ++) {

        // This cannot be true with the inputMask set, as there will be space characters
        if (list[index ].isEmpty()) {
            emptyGroup = true;
            continue;
        }

        int value = list[index ].toInt(&integer);
        if (!integer) {
            return Invalid;
        } else if ( (0 > value) || ( 255 < value) ) {
            return Invalid;
        }

    }

    if ( (4 != list.size ()) || (emptyGroup) ) {
        return Intermediate;
    }

    input = list.join(".");
    return Acceptable;
}

