#ifndef VSNIPPETLIST_H
#define VSNIPPETLIST_H

#include <QWidget>
#include <QVector>
#include <QPoint>

#include "vsnippet.h"
#include "vnavigationmode.h"

class QPushButton;
class QListWidget;
class QListWidgetItem;
class QLabel;
class QAction;
class QKeyEvent;


class VSnippetList : public QWidget, public VNavigationMode
{
    Q_OBJECT
public:
    explicit VSnippetList(QWidget *p_parent = nullptr);

    // Implementations for VNavigationMode.
    void showNavigation() Q_DECL_OVERRIDE;
    bool handleKeyNavigation(int p_key, bool &p_succeed) Q_DECL_OVERRIDE;

protected:
    void keyPressEvent(QKeyEvent *p_event) Q_DECL_OVERRIDE;

private slots:
    void newSnippet();

    void manageSnippetShortcut();

    void handleContextMenuRequested(QPoint p_pos);

    void handleItemActivated(QListWidgetItem *p_item);

    void snippetInfo();

    void deleteSelectedItems();

    void sortItems();

private:
    void setupUI();

    void initActions();

    void initShortcuts();

    void makeSureFolderExist() const;

    // Update list of snippets according to m_snippets.
    void updateContent();

    // Add @p_snippet.
    bool addSnippet(const VSnippet &p_snippet, QString *p_errMsg = nullptr);

    // Write m_snippets to config file.
    bool writeSnippetsToConfig() const;

    // Read from config file to m_snippets.
    bool readSnippetsFromConfig();

    // Get the snippet index in m_snippets of @p_item.
    int getSnippetIndex(QListWidgetItem *p_item) const;

    VSnippet *getSnippet(QListWidgetItem *p_item);

    // Write the content of @p_snippet to file.
    bool writeSnippetFile(const VSnippet &p_snippet, QString *p_errMsg = nullptr);

    QString getSnippetFilePath(const VSnippet &p_snippet) const;

    // Sort m_snippets according to @p_sortedIdx.
    bool sortSnippets(const QVector<int> &p_sortedIdx, QString *p_errMsg = nullptr);

    bool deleteSnippets(const QList<QString> &p_snippets, QString *p_errMsg = nullptr);

    bool deleteSnippetFile(const VSnippet &p_snippet, QString *p_errMsg = nullptr);

    QPushButton *m_addBtn;
    QPushButton *m_shortcutBtn;
    QPushButton *m_locateBtn;
    QLabel *m_numLabel;
    QListWidget *m_snippetList;

    QAction *m_applyAct;
    QAction *m_infoAct;
    QAction *m_deleteAct;
    QAction *m_sortAct;

    QVector<VSnippet> m_snippets;

    static const QString c_infoShortcutSequence;
};

#endif // VSNIPPETLIST_H
