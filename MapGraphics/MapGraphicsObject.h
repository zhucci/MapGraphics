#ifndef MAPGRAPHICSOBJECT_H
#define MAPGRAPHICSOBJECT_H

#include <QObject>
#include <QPointF>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsItem>

#include "MapGraphics_global.h"

class MAPGRAPHICSSHARED_EXPORT MapGraphicsObject : public QObject
{
    Q_OBJECT

public:
    enum MapGraphicsObjectFlag
    {
        ObjectIsMovable = 0x01,
        ObjectIsSelectable
    };
    Q_DECLARE_FLAGS(MapGraphicsObjectFlags,MapGraphicsObjectFlag)

    //PrivateQGraphicsObject will call some of our protected event handlers that nobody else needs to touch
    friend class PrivateQGraphicsObject;
public:
    explicit MapGraphicsObject(bool sizeIsZoomInvariant=false,MapGraphicsObject *parent = 0);
    virtual ~MapGraphicsObject();

    bool sizeIsZoomInvariant() const;

    /*!
     \brief You need to implement this. If sizeIsZoomInvariant() is true, this should return the size of the
     rectangle you want in PIXELS. If false, this should return the size of the rectangle in METERS. The
     rectangle should be centered at (0,0) regardless.

     \return QRectF
    */
    virtual QRectF boundingRect() const=0;

    /**
     * @brief Paints the contents of the Object in ENU coordinates --- the same coordinates as boundingRect.
     * You must implement this.
     *
     * @param painter
     * @param option
     * @param widget
     */
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget=0)=0;

    bool enabled() const;
    void setEnabled(bool);

    qreal opacity() const;
    void setOpacity(qreal);

    MapGraphicsObject * parent() const;
    void setParent(MapGraphicsObject *);

    QPointF pos() const;
    virtual void setPos(const QPointF&);

    qreal rotation() const;
    void setRotation(qreal);

    bool visible() const;
    void setVisible(bool);

    qreal longitude() const;
    void setLongitude(qreal);

    qreal latitude() const;
    void setLatitude(qreal);

    qreal zValue() const;
    void setZValue(qreal);

    bool isSelected() const;
    void setSelected(bool);

    void setFlag(MapGraphicsObjectFlag, bool enabled=true);
    void setFlags(MapGraphicsObject::MapGraphicsObjectFlags);
    MapGraphicsObject::MapGraphicsObjectFlags flags() const;

protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent * event);
    virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value);
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void keyReleaseEvent(QKeyEvent * event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    virtual void wheelEvent(QGraphicsSceneWheelEvent * event);

    
signals:
    void enabledChanged();
    void opacityChanged();
    void parentChanged();
    void posChanged();
    void rotationChanged();
    void visibleChanged();
    void zValueChanged();

    void flagsChanged();

    //Please do not use this. It should only be used internally for now. Ugly, I know.
    void selectedChanged();

    void newObjectGenerated(MapGraphicsObject *);

    
public slots:

private:
    bool _sizeIsZoomInvariant;

    bool _enabled;
    qreal _opacity;
    MapGraphicsObject * _parent;
    QPointF _pos;
    qreal _rotation;
    bool _visible;
    qreal _zValue;
    bool _selected;

    MapGraphicsObject::MapGraphicsObjectFlags _flags;
    
};
Q_DECLARE_OPERATORS_FOR_FLAGS(MapGraphicsObject::MapGraphicsObjectFlags)

#endif // MAPGRAPHICSOBJECT_H