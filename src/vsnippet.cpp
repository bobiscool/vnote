#include "vsnippet.h"

#include <QObject>
#include <QDebug>
#include "vconstants.h"

const QString VSnippet::c_defaultCursorMark = "@@";

const QString VSnippet::c_defaultSelectionMark = "$$";

QVector<QChar> VSnippet::s_allShortcuts;

VSnippet::VSnippet()
    : m_type(Type::PlainText),
      m_cursorMark(c_defaultCursorMark)
{
}

VSnippet::VSnippet(const QString &p_name,
                   Type p_type,
                   const QString &p_content,
                   const QString &p_cursorMark,
                   const QString &p_selectionMark,
                   QChar p_shortcut)
    : m_name(p_name),
      m_type(p_type),
      m_content(p_content),
      m_cursorMark(p_cursorMark),
      m_selectionMark(p_selectionMark),
      m_shortcut(p_shortcut)
{
    Q_ASSERT(m_selectionMark != m_cursorMark);
}

bool VSnippet::update(const QString &p_name,
                      Type p_type,
                      const QString &p_content,
                      const QString &p_cursorMark,
                      const QString &p_selectionMark,
                      QChar p_shortcut)
{
    bool updated = false;
    if (m_name != p_name) {
        m_name = p_name;
        updated = true;
    }

    if (m_type != p_type) {
        m_type = p_type;
        updated = true;
    }

    if (m_content != p_content) {
        m_content = p_content;
        updated = true;
    }

    if (m_cursorMark != p_cursorMark) {
        m_cursorMark = p_cursorMark;
        updated = true;
    }

    if (m_selectionMark != p_selectionMark) {
        m_selectionMark = p_selectionMark;
        updated = true;
    }

    if (m_shortcut != p_shortcut) {
        m_shortcut = p_shortcut;
        updated = true;
    }

    return updated;
}

QString VSnippet::typeStr(VSnippet::Type p_type)
{
    switch (p_type) {
    case Type::PlainText:
        return QObject::tr("PlainText");

    case Type::Html:
        return QObject::tr("Html");

    default:
        return QObject::tr("Invalid");
    }
}

QJsonObject VSnippet::toJson() const
{
    QJsonObject snip;
    snip[SnippetConfig::c_name] = m_name;
    snip[SnippetConfig::c_type] = (int)m_type;
    snip[SnippetConfig::c_cursorMark] = m_cursorMark;
    snip[SnippetConfig::c_selectionMark] = m_selectionMark;
    snip[SnippetConfig::c_shortcut] = QString(m_shortcut);

    return snip;
}

VSnippet VSnippet::fromJson(const QJsonObject &p_json)
{
    QChar shortcut;
    QString shortcutStr = p_json[SnippetConfig::c_shortcut].toString();
    if (!shortcutStr.isEmpty()) {
        isEmpty
    }

    VSnippet snip(p_json[SnippetConfig::c_name].toString(),
                  static_cast<VSnippet::Type>(p_json[SnippetConfig::c_type].toInt()),
                  "",
                  p_json[SnippetConfig::c_cursorMark].toString(),
                  p_json[SnippetConfig::c_selectionMark].toString(),
                  p_json[SnippetConfig::c_shortcut].toChar());

    return snip;
}

const QVector<QChar> &VSnippet::getAllShortcuts()
{
    if (s_allShortcuts.isEmpty()) {
        // Init.
        QChar ch('a');
        while (true) {
            s_allShortcuts.append(ch);
            if (ch == 'z') {
                break;
            }

            ch++;
        }
    }

    return s_allShortcuts;
}
