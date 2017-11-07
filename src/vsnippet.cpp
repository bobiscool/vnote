#include "vsnippet.h"

#include <QObject>
#include <QDebug>
#include "vconstants.h"

const QString VSnippet::c_defaultCursorMark = "@@";

const QString VSnippet::c_defaultSelectionMark = "$$";

VSnippet::VSnippet()
    : m_type(Type::PlainText),
      m_cursorMark(c_defaultCursorMark)
{
}

VSnippet::VSnippet(const QString &p_name,
                   Type p_type,
                   const QString &p_content,
                   const QString &p_cursorMark,
                   const QString &p_selectionMark)
    : m_name(p_name),
      m_type(p_type),
      m_content(p_content),
      m_cursorMark(p_cursorMark),
      m_selectionMark(p_selectionMark)
{
    Q_ASSERT(m_selectionMark != m_cursorMark);
}

bool VSnippet::update(const QString &p_name,
                      Type p_type,
                      const QString &p_content,
                      const QString &p_cursorMark,
                      const QString &p_selectionMark)
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

    return snip;
}

VSnippet VSnippet::fromJson(const QJsonObject &p_json)
{
    VSnippet snip(p_json[SnippetConfig::c_name].toString(),
                  static_cast<VSnippet::Type>(p_json[SnippetConfig::c_type].toInt()),
                  "",
                  p_json[SnippetConfig::c_cursorMark].toString(),
                  p_json[SnippetConfig::c_selectionMark].toString());

    return snip;
}
