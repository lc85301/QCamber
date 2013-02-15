#include "octagonsymbol.h"

#include <QtGui>
#include <QRegExp>

OctagonSymbol::OctagonSymbol(QString def, Polarity polarity):
    Symbol("oct", "oct([0-9.]+)x([0-9.]+)x([0-9.]+)", polarity), m_def(def)
{
  QRegExp rx(m_pattern);
  if (!rx.exactMatch(def))
    throw InvalidSymbolException(def.toAscii());

  QStringList caps = rx.capturedTexts();
  m_w = caps[1].toDouble() / 1000.0;
  m_h = caps[2].toDouble() / 1000.0;
  m_r = caps[3].toDouble() / 1000.0;

  painterPath();
}

QPainterPath OctagonSymbol::painterPath(void)
{
  if (m_valid)
    return m_cachedPath;

  m_cachedPath = QPainterPath();

  qreal x = -m_w / 2;
  qreal y = -m_h / 2;

  m_cachedPath.moveTo(x, y+m_h-m_r);
  m_cachedPath.lineTo(x, y+m_r);
  m_cachedPath.lineTo(x+m_r, y);
  m_cachedPath.lineTo(x+m_w-m_r, y);
  m_cachedPath.lineTo(x+m_w, y+m_r);
  m_cachedPath.lineTo(x+m_w, y+m_h-m_r);
  m_cachedPath.lineTo(x+m_w-m_r, y+m_h);
  m_cachedPath.lineTo(x+m_r, y+m_h);
  m_cachedPath.closeSubpath();

ret:
  prepareGeometryChange();
  m_bounding = m_cachedPath.boundingRect();
  m_valid = true;

  return m_cachedPath;
}
