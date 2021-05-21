#ifndef D_LUATABLE_H
#define D_LUATABLE_H

#include <QVariant>
#include <QMetaType>
#include "luafunction.h"
class LuaVM;

class LuaTableRef {
friend class LuaVM;
friend class RefScope;
public:
  ~LuaTableRef();

  QVariantList keys() const;

  bool has(int key) const;
  QVariant get(int key) const;
  inline void set(int key, const LuaFunction& value) { set(key, QVariant::fromValue(value)); }
  void set(int key, const QVariant& value);

  bool has(const QString& key) const;
  QVariant get(const QString& key) const;
  inline void set(const QString& key, const LuaFunction& value) { set(key, QVariant::fromValue(value)); }
  void set(const QString& key, const QVariant& value);
  QVariant call(const QString& key, const QVariantList& args) const;

  // TODO: QVariant keys? Template keys?

private:
  LuaTableRef(LuaVM* lua);
  LuaTableRef(LuaVM* lua, int ref);

  void pushStack() const;

  LuaVM* lua;
  int ref;
};
using LuaTable = QSharedPointer<LuaTableRef>;
Q_DECLARE_METATYPE(LuaTable);

#endif