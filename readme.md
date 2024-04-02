# 简介
一个C++11写的计算图框架，结构清晰简单。

# V1版本（graph_v1）

## 概念

1. Node：计算节点
2. Graph：计算图，节点相互关联构成有向无环图
3. DataCenter：数据中心，是一个struct，在节点之间传递数据

## 设计

1. Graph负责Node的有向无环图的构建，Node之间采用使用future和promise控制时机，以及数据的传递
2. Node从future中获取DataCenter，并将结果写入到DataCenter中，传递给下一个节点

# V2版本（graph_v2）

## 概念

1. Node：计算节点
2. Graph：计算图，节点相互关联构成有向无环图
3. DataCenter：数据中心，负责存储数据，采用单例模式

## 设计

1. Graph负责Node的有向无环图的构建，Node之间采用使用future和promise控制时机。
2. DataCenter采用单例模式，各个节点可以自由的在其中存取数据

# V3版本（graph_v3）

## 概念

1. Node：计算节点
2. Graph：计算图，节点相互关联构成有向无环图
3. Message：数据载体，在不同Node之间传递数据
4. Conduit：消息中介，发送和接受Message

## 设计

1. 核心采用中介者模式，Conduit充当中介者。在Conduit中可以发布和订阅topic，并且可以在指定的topic上发送数据。
2. 每个节点需要用的数据都组织在Message中，如果增加或者删除节点，需要修改Message中的数据结构，不符合开闭原则。
3. Graph中持有Conduit的指针，在构造Node的时候，将其传递给Node。Node便可以发布和订阅消息。

# 总结
1. 总体上实现了有向无环图，并且节点之前可以自由传递数据。
2. 没有依赖关系的节点可以并行执行
3. 节点之间的依赖关系是相对固定，并不能无约束的自由组合。比如，Node2依赖Node1，Node3依赖Node1，Node2和Node3之间没有依赖关系。那么在构造计算图的时候可以选择不要Node2，或者Node3，但是Node1必须存在。

# 未来计划
1. 增加线程池
2. 增加无锁的数据结构
