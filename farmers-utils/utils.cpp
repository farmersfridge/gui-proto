#include "utils.h"
#include <QDirIterator>
#include <QTextStream>

// To local file:
QString Utils::toLocalFile(const QString &input)
{
    QUrl url(input);
    return url.isLocalFile() ? url.toLocalFile() : input;
}

// From local file:
QString Utils::fromLocalFile(const QString &input)
{
    QUrl url(input);
    return !url.isLocalFile() ? QUrl::fromLocalFile(input).toString() : input;
}

// Return application directory:
QDir Utils::appDir()
{
    return QDir(QCoreApplication::applicationDirPath());
}

// Get files  recursively:
void Utils::files(const QString &srcDir, const QStringList &imageFilters, QStringList &files)
{
    files.clear();
    if (imageFilters.isEmpty())
        return;

    QDirIterator it(srcDir, imageFilters, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        files << fromLocalFile(it.next());
}

// Return path to settings dir:
QDir Utils::pathToSettingsDir()
{
    // Find settings dir:
    QDir settingsDir = appDir();

    // Path to settings dir:
    settingsDir.cdUp();
    settingsDir.cd("menuviewer");
    settingsDir.mkdir("settings");
    settingsDir.cd("settings");

    return settingsDir;
}

// Return path to settings files:
QString Utils::pathToSettingsFile(const QString &sSettingsFile)
{
    // Get settings dir path:
    return pathToSettingsDir().absoluteFilePath(sSettingsFile);
}

// Clear directory:
bool Utils::clearDirectory(const QString &dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = clearDirectory(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }

    return result;
}

// Save byte array to file:
bool Utils::save(const QByteArray &bArray, const QString &filePath)
{
    if (bArray.isEmpty() || bArray.isNull())
        return false;
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(bArray);
        file.close();
    }
    return true;
}

// Returns empty QByteArray() on failure.
QString Utils::fileCheckSum(const QString &sFileName,
                            QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile f(sFileName);
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&f)) {
            return QString::fromLatin1(hash.result().toHex());
        }
        f.close();
    }
    return "";
}

// Clear string (remove non alphanumerical characters):
QString Utils::clearString(const QString &sInput)
{
    QString sClear = sInput;
    return sClear.remove(QRegExp("[^a-zA-Z\\d\\s]"));
}

// Validate email address:
bool Utils::validateEmailAddress(const QString &emailAddress)
{
    QRegExp regex("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
    return regex.exactMatch(emailAddress);
}

// Get key:
QString Utils::getKey(const QString &input)
{
    return input.simplified().toLower();
}
