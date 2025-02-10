#include <QtWidgets/qwidget.h>
#include <QtCore/qtextcodec.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qstring.h>
#include <String>
#include <vector>
#include <iostream>
#include <QtWidgets/qmessagebox.h>
class QC {
public:
	std::vector<QString> contents;
	QC(const std::vector<std::string>& content) {
	for (auto indexcontent : content) {
		QTextCodec* Codec = QTextCodec::codecForName("GBK");
		QString Qcontent = Codec->toUnicode(indexcontent.c_str());
	contents.push_back(Qcontent);
	}
	}
};
inline void SHOWERROR(QString content) {
	QMessageBox::warning(nullptr, "error", content);
}


inline ::QString QCT(const char* content) {
		QTextCodec* Codec = QTextCodec::codecForName("GBK");
		QString Qcontent = Codec->toUnicode(content);
		return Qcontent;
	}
inline QStringList QCTLT(std::vector<const char*>& vcc) {
	QStringList  Result;
	for (const auto& content : vcc) {
		Result.append(QCT(content));
	}
	return Result;
}
inline QString SingleQRB(QString& qc,char tar) {
	int check = 0;
	//check
	for (auto& qcr : qc) {
		if (qcr == tar) {
			check += 1;
		}
	}
	if (check == 1) {
	QString Result(QCT(""));
	QString middle(QCT(""));
	bool if_(true);
	for (auto& per : qc) {
		if (per != tar and if_) {
			Result += per;
		}
		else if (per == tar) { Result = per + Result; if_ = false; }
		else  {
			middle += per;
		}
	}
	Result = middle + Result;
	return Result;}
	else {
		QChar qc(tar);
		QString response1 = QCT("Repeating \"") + tar + QCT("\"") + QCT(" or no \"") + tar + QCT("\"");
		QString response2 = QCT("SingleQRB accepts a QString just includes one \"") + tar + QCT("\"");
		QMessageBox::information(nullptr,response1 , response2);
		return 0;
	}

}