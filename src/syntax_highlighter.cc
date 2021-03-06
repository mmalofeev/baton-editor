#include "syntax_highlighter.h"

#include <QColor>
#include <QPalette>
#include <QTextDocument>
#include <cmath>
#include <iostream>
#include <string>

namespace {
// http://alienryderflex.com/hsp.html
bool isLight(int r, int g, int b) {  // in hex
  double brightness = std::sqrt(0.299 * r * r + 0.587 * g * g + 0.114 * b * b);
  return brightness > (255.0 / 2);
}

}  // namespace

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
  HighlightingRule rule;

  QColor color = QPalette().color(QPalette::Window); /*name().toStdString();*/
  int r, g, b;
  color.getRgb(&r, &g, &b);
  bool is_light = isLight(r, g, b);

  QColor keywordColor = is_light ? Qt::darkBlue : QColor("#63ceff");
  QColor classColor = is_light ? Qt::darkMagenta : QColor("");
  QColor commentColor = is_light ? Qt::red : QColor("#ff4646");
  QColor quotationColor = is_light ? Qt::darkGreen : QColor("#76ff3d");
  QColor functionColor = is_light ? Qt::blue : QColor("#625df3");
  QColor returnColor = is_light ? Qt::darkMagenta : QColor("#ffa602");
  QColor condCycleColor = is_light ? Qt::magenta : QColor("#ff6df6");
  QColor streamColor = is_light ? Qt::darkGreen : QColor("#f4bbff");

  keywordFormat.setForeground(keywordColor);
  keywordFormat.setFontWeight(QFont::Bold);

  const QString keywordPatterns[] = {
      QStringLiteral("\\bchar\\b"),
      QStringLiteral("\\bclass\\b"),
      QStringLiteral("\\bconst\\b"),
      QStringLiteral("\\bdouble\\b"),
      QStringLiteral("\\benum\\b"),
      QStringLiteral("\\bexplicit\\b"),
      QStringLiteral("\\bfriend\\b"),
      QStringLiteral("\\binline\\b"),
      QStringLiteral("\\bint\\b"),
      QStringLiteral("\\blong\\b"),
      QStringLiteral("\\bnamespace\\b"),
      QStringLiteral("\\boperator\\b"),
      QStringLiteral("\\bprivate\\b"),
      QStringLiteral("\\bprotected\\b"),
      QStringLiteral("\\bpublic\\b"),
      QStringLiteral("\\bshort\\b"),
      QStringLiteral("\\bsignals\\b"),
      QStringLiteral("\\bsigned\\b"),
      QStringLiteral("\\bslots\\b"),
      QStringLiteral("\\bstatic\\b"),
      QStringLiteral("\\bstruct\\b"),
      QStringLiteral("\\btemplate\\b"),
      QStringLiteral("\\btypedef\\b"),
      QStringLiteral("\\btypename\\b"),
      QStringLiteral("\\bunion\\b"),
      QStringLiteral("\\bunsigned\\b"),
      QStringLiteral("\\bvirtual\\b"),
      QStringLiteral("\\bvoid\\b"),
      QStringLiteral("\\bvolatile\\b"),
      QStringLiteral("\\bbool\\b"),
      QStringLiteral("\\busing\\b"),
      QStringLiteral("\\bstring\\b"),
      QStringLiteral("\\bvector\\b"),
      QStringLiteral("\\bstd::vector\\b"),
      QStringLiteral("\\bstd::string\\b"),
      QStringLiteral("\\bunordered_map\\b"),
      QStringLiteral("\\bstd::unordered_map\\b"),
      QStringLiteral("\\bstack\\b"),
      QStringLiteral("\\bstd::stack\\b"),
      QStringLiteral("\\bmap\\b"),
      QStringLiteral("\\bstd::map\\b"),
      QStringLiteral("\\blist\\b"),
      QStringLiteral("\\bstd::list\\b"),
      QStringLiteral("\\bpriority_queue\\b"),
      QStringLiteral("\\bstd::priority_queue\\b"),
      QStringLiteral("\\bqueue\\b"),
      QStringLiteral("\\bstd::queue\\b"),
      QStringLiteral("\\bdeque\\b"),
      QStringLiteral("\\bstd::deque\\b"),
      QStringLiteral("\\bint32_t\\b"),
      QStringLiteral("\\bfunction\\b"),
      QStringLiteral("\\bstd::function\\b"),
      QStringLiteral("\\bfloat\\b"),
      QStringLiteral("\\buint32_t\\b"),
      QStringLiteral("\\bint64_t\\b"),
      QStringLiteral("\\buint64_t\\b"),
      QStringLiteral("\\bint16_t\\b"),
      QStringLiteral("\\buint16_t\\b"),
      QStringLiteral("\\bint8_t\\b"),
      QStringLiteral("\\buint8_t\\b"),
      QStringLiteral("\\bchar32_t\\b"),
      QStringLiteral("\\bchar16_t\\b"),
      QStringLiteral("\\breturn\\b"),
      QStringLiteral("\\bif\\b"),
      QStringLiteral("\\belse\\b"),
      QStringLiteral("\\binclude\\b"),
      QStringLiteral("\\bfor\\b"),
      QStringLiteral("\\bcwhile\\b"),
      QStringLiteral("\\bswitch\\b"),
      QStringLiteral("\\bcase\\b"),
      QStringLiteral("\\bstd::stringstream\\b"),
      QStringLiteral("\\bstringstream\\b"),
      QStringLiteral("\\bstd::cerr\\b"),
      QStringLiteral("\\bcerr\\b"),
      QStringLiteral("\\bcout\\b"),
      QStringLiteral("\\bstd::cout\\b"),
      QStringLiteral("\\bcin\\b"),
      QStringLiteral("\\bstd::cin\\b"),
      QStringLiteral("\\bifstream\\b"),
      QStringLiteral("\\bstd::ifstream\\b"),
      QStringLiteral("\\bistream\\b"),
      QStringLiteral("\\bstd::istream\\b"),
      QStringLiteral("\\bostream\\b"),
      QStringLiteral("\\bofstream\\b"),
      QStringLiteral("\\bstd::ostream\\b"),
      QStringLiteral("\\bstd::ofstream\\b"),
      QStringLiteral("\\bprintf\\b"),
      QStringLiteral("\\bscanf\\b"),
      QStringLiteral("\\bfprintf\\b"),
      QStringLiteral("\\bfscanf\\b"),
      QStringLiteral("\\bset\\b"),
      QStringLiteral("\\bstd::set\\b"),
      QStringLiteral("\\bstd::pair\\b"),
      QStringLiteral("\\bpair\\b"),
      QStringLiteral("\\bunordered_set\\b"),
      QStringLiteral("\\bstd::unordered_set\\b"),
      QStringLiteral("\\bbitset\\b"),
      QStringLiteral("\\bstd::bitset\\b"),
      QStringLiteral("\\btrue\\b"),
      QStringLiteral("\\bfalse\\b"),
      QStringLiteral("\\bauto\\b"),
      QStringLiteral("\\bdecltype\\b"),
      QStringLiteral("\\btemplate\\b"),
      QStringLiteral("\\bsizeof...\\b"),
      QStringLiteral("\\bsize\\b")};
  for (const QString &pattern : keywordPatterns) {
    rule.pattern = QRegularExpression(pattern);
    rule.format = keywordFormat;
    highlightingRules.append(rule);
  }

  singleLineCommentFormat.setForeground(commentColor);
  rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
  rule.format = singleLineCommentFormat;
  highlightingRules.append(rule);

  multiLineCommentFormat.setForeground(commentColor);
  quotationFormat.setForeground(quotationColor);
  rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
  rule.format = quotationFormat;
  highlightingRules.append(rule);

  //  functionFormat.setFontItalic(true);
  functionFormat.setForeground(functionColor);
  functionFormat.setFontWeight(QFont::Bold);
  rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
  rule.format = functionFormat;
  highlightingRules.append(rule);

  returnFormat.setForeground(returnColor);
  rule.pattern = QRegularExpression(QStringLiteral("\\breturn\\b"));
  rule.format = returnFormat;
  highlightingRules.append(rule);

  conditionalStatementsFormat.setForeground(condCycleColor);
  conditionalStatementsFormat.setFontWeight(QFont::Bold);
  rule.pattern = QRegularExpression(QStringLiteral("\\b(if|else)\\b"));
  rule.format = conditionalStatementsFormat;
  highlightingRules.append(rule);

  conditionalCyclesFormat.setForeground(condCycleColor);
  conditionalCyclesFormat.setFontWeight(QFont::Bold);
  rule.pattern =
      QRegularExpression(QStringLiteral("\\b(while|for|switch|case)\\b"));
  rule.format = conditionalCyclesFormat;
  highlightingRules.append(rule);

  streamFormat.setForeground(streamColor);
  streamFormat.setFontWeight(QFont::Bold);
  rule.pattern = QRegularExpression(QStringLiteral(
      "\\b(std::stringstream|stringstream|std::cerr|std::cout|cerr|cout|cin|"
      "std::cin|ifstream|std::ifstream|istream|std::istream|ostream|std::"
      "ostream|ofstream|std::ofstream|printf|scanf|fprintf|fscanf)\\b"));
  rule.format = streamFormat;
  highlightingRules.append(rule);

  commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
  commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
}

void Highlighter::highlightBlock(const QString &text) {
  for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
    QRegularExpressionMatchIterator matchIterator =
        rule.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
      QRegularExpressionMatch match = matchIterator.next();
      setFormat(match.capturedStart(), match.capturedLength(), rule.format);
    }
  }
  setCurrentBlockState(0);

  int startIndex = 0;
  if (previousBlockState() != 1)
    startIndex = text.indexOf(commentStartExpression);

  while (startIndex >= 0) {
    QRegularExpressionMatch match =
        commentEndExpression.match(text, startIndex);
    int endIndex = match.capturedStart();
    int commentLength = 0;
    if (endIndex == -1) {
      setCurrentBlockState(1);
      commentLength = text.length() - startIndex;
    } else {
      commentLength = endIndex - startIndex + match.capturedLength();
    }
    setFormat(startIndex, commentLength, multiLineCommentFormat);
    startIndex =
        text.indexOf(commentStartExpression, startIndex + commentLength);
  }
}
