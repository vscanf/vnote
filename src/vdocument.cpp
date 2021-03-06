#include "vdocument.h"
#include "vfile.h"
#include <QDebug>

VDocument::VDocument(const VFile *v_file, QObject *p_parent)
    : QObject(p_parent),
      m_file(v_file),
      m_readyToHighlight(false)
{
}

void VDocument::updateText()
{
    if (m_file) {
        emit textChanged(m_file->getContent());
    }
}

void VDocument::setToc(const QString &toc, int /* baseLevel */)
{
    if (toc == m_toc) {
        return;
    }
    m_toc = toc;
    emit tocChanged(m_toc);
}

QString VDocument::getToc()
{
    return m_toc;
}

void VDocument::scrollToAnchor(const QString &anchor)
{
    m_header = anchor;

    emit requestScrollToAnchor(anchor);
}

void VDocument::setHeader(const QString &anchor)
{
    if (anchor == m_header) {
        return;
    }

    m_header = anchor;
    emit headerChanged(m_header);
}

void VDocument::setHtml(const QString &html)
{
    if (html == m_html) {
        return;
    }
    m_html = html;
    emit htmlChanged(m_html);
}

void VDocument::setLog(const QString &p_log)
{
    qDebug() << "JS:" << p_log;
    emit logChanged(p_log);
}

void VDocument::keyPressEvent(int p_key, bool p_ctrl, bool p_shift)
{
    emit keyPressed(p_key, p_ctrl, p_shift);
}

void VDocument::highlightTextAsync(const QString &p_text, int p_id, int p_timeStamp)
{
    emit requestHighlightText(p_text, p_id, p_timeStamp);
}

void VDocument::highlightTextCB(const QString &p_html, int p_id, int p_timeStamp)
{
    emit textHighlighted(p_html, p_id, p_timeStamp);
}

void VDocument::textToHtmlAsync(const QString &p_text)
{
    emit requestTextToHtml(p_text);
}

void VDocument::getHtmlContentAsync()
{
    emit requestHtmlContent();
}

void VDocument::textToHtmlCB(const QString &p_text, const QString &p_html)
{
    emit textToHtmlFinished(p_text, p_html);
}

void VDocument::noticeReadyToHighlightText()
{
    m_readyToHighlight = true;
    emit readyToHighlightText();
}

void VDocument::noticeReadyToTextToHtml()
{
    m_readyToTextToHtml = true;
}

void VDocument::setFile(const VFile *p_file)
{
    m_file = p_file;
}

void VDocument::finishLogics()
{
    qDebug() << "Web side finished logics";
    emit logicsFinished();
}

void VDocument::htmlContentCB(const QString &p_head,
                              const QString &p_style,
                              const QString &p_body)
{
    emit htmlContentFinished(p_head, p_style, p_body);
}
