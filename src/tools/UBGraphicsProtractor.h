/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UBGRAPHICSPROTRACTOR_H_
#define UBGRAPHICSPROTRACTOR_H_

#include <QtGui>
#include <QtSvg>

#include "core/UB.h"
#include "tools/UBAbstractDrawRuler.h"
#include "domain/UBItem.h"

class UBGraphicsScene;

class UBGraphicsProtractor : public UBAbstractDrawRuler, public QGraphicsEllipseItem, public UBItem
{

    Q_OBJECT

    public:
        UBGraphicsProtractor ();
		enum Tool {None, Move, Resize, Rotate, Reset, Close, MoveMarker};

        qreal angle () { return mStartAngle; }
        qreal markerAngle () { return mCurrentAngle; }
        void  setAngle (qreal angle) { mStartAngle = angle; setStartAngle(mStartAngle * 16); }
        void  setMarkerAngle (qreal angle) { mCurrentAngle = angle; }

        virtual UBItem* deepCopy() const;

        enum { Type = UBGraphicsItemType::ProtractorItemType };

        virtual int type() const
        {
            return Type;
        }

    protected:
        virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *styleOption, QWidget *widget);

        virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

        virtual void   mousePressEvent (QGraphicsSceneMouseEvent *event);
        virtual void    mouseMoveEvent (QGraphicsSceneMouseEvent *event);
        virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);
        virtual void   hoverEnterEvent (QGraphicsSceneHoverEvent *event);
        virtual void   hoverLeaveEvent (QGraphicsSceneHoverEvent *event);
        virtual void    hoverMoveEvent (QGraphicsSceneHoverEvent *event);
        virtual QPainterPath shape() const;
        QRectF boundingRect() const;

    private:
        // Helpers
        void paintGraduations (QPainter *painter);
        void paintButtons (QPainter *painter);
        void paintAngleMarker (QPainter *painter);
        Tool toolFromPos (QPointF pos);
        qreal antiScale () const;
        UBGraphicsScene*            scene() const;
        QBrush                  fillBrush() const;

        QSizeF buttonSizeReference () const{return QSizeF(radius() / 10, mCloseSvgItem->boundingRect().height() * radius()/(10 * mCloseSvgItem->boundingRect().width()));}
        QSizeF markerSizeReference () const{return QSizeF(radius() / 10, mMarkerSvgItem->boundingRect().height() * radius()/(10 * mMarkerSvgItem->boundingRect().width()));}
        QRectF	resetButtonRect () const;
        QRectF	closeButtonRect () const;
        QRectF	resizeButtonRect () const;
        QRectF	rotateButtonRect () const{return QRectF(buttonSizeReference().width() * 5.5, -buttonSizeReference().width() * 5, buttonSizeReference().width(), buttonSizeReference().width());}
        QRectF	markerButtonRect () const{return QRectF(radius() + 3, -markerSizeReference().height() / 2 , markerSizeReference().width(), markerSizeReference().height());}
                inline qreal               radius () const{return rect().height() / 2 - 20;}

        // Members
        QPointF mPreviousMousePos;
        Tool    mCurrentTool;
        bool	mShowButtons;
        qreal   mCurrentAngle;
        qreal   mSpan;
        qreal   mStartAngle;
        qreal   mScaleFactor;

        QGraphicsSvgItem* mResetSvgItem;
        QGraphicsSvgItem* mResizeSvgItem;
        QGraphicsSvgItem* mMarkerSvgItem;
		QGraphicsSvgItem* mRotateSvgItem;

        static const QRectF sDefaultRect;

        virtual void rotateAroundCenter(qreal angle);
        virtual QPointF	rotationCenter() const;

        int    sFillTransparency;
        int    sDrawTransparency;
};

#endif /* UBGRAPHICSPROTRACTOR_H_ */
