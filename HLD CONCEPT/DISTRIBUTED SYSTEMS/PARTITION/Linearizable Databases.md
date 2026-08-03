# 🔥 Linearizable Storage - "Jo Latest Hai, Wahi Sabko Dikhe!" 🚀

> ## 🎯 One Line Definition
>
> **Linearizable Storage** ek aisa distributed storage system hai jo ensure karta hai ki:
>
> - ✅ System fault tolerant ho
> - ✅ Sab writes ek global order me ho
> - ✅ Kisi bhi read ko hamesha latest successful write hi dikhe
>
> **Simple Language👇**
>
> > **"Jo write pehle ho chuka hai, uske baad kabhi bhi purana data read nahi hona chahiye."**

---

# 🤔 Sabse Pehle Problem Samjho

Suppose tumhare paas ek distributed database hai.

```
          Client

             |

      ----------------

      |              |

    Node A        Node B
```

Ab maan lo...

Initially

```
Leader = Node A
```

Sabko pata hai.

---

Ab election hua.

Naya leader ban gaya.

```
Leader = Node B
```

Ye information database me write ho gayi.

---

Ab ek client read karta hai.

Usko kya milna chahiye?

Obviously

```
Node B
```

---

Lekin agar usko mila

```
Node A
```

😱😱😱

Problem.

System purana state dikha raha hai.

Ye allowed nahi hai.

Isi property ko bolte hain

# ⭐ Linearizability

---

# Real Life Example 🏦

Imagine bank account.

Balance

```
₹1000
```

Tumne ATM se

```
Withdraw ₹500
```

Successfully ho gaya.

Ab immediately balance check kiya.

Expected

```
₹500
```

Agar ATM bole

```
₹1000
```

😂😂

Bank pe trust hi khatam.

Exactly yehi non-linearizable system hota.

---

# Another Example 📱

WhatsApp

Tumne profile photo change ki.

Immediately friend dekhta hai.

Usko kya dikhna chahiye?

```
New Photo
```

Na ki

```
Old Photo
```

---

# Another Example 🍔

Swiggy

Restaurant

```
Burger Out Of Stock
```

Write ho gaya.

Ab customer app open kare.

Usko

```
Available
```

dikh raha.

Order fail.

Customer gussa.

Problem.

---

# Formal Definition 📚

Agar

```
Write Complete

↓

Then Read Happens
```

To

```
Read MUST return

Latest Write
```

Always.

---

# Visualization 🎯

```
Time →

Write(A)

↓

Write(B)

↓

Read

```

Read should return

```
B
```

Never

```
A
```

---

# Why Is This So Important?

Distributed systems me

```
Multiple Machines

↓

Multiple Copies

↓

Network Delay

↓

Failures
```

Agar latest state nahi mila

System inconsistent ho jayega.

---

# Core Requirement Of Linearizability

## Two Things

```
1.

Fault Tolerant
```

AND

```
2.

Ordered Writes
```

---

# Why Ordered Writes?

Imagine

Two writes aaye.

```
Write1

Leader=A
```

Aur

```
Write2

Leader=B
```

Agar different machines different order me apply kar dein

Machine1

```
A

↓

B
```

Machine2

```
B

↓

A
```

😂😂

Ab dono disagree karenge.

Impossible.

---

Hence

Sabko same order follow karna hoga.

---

# Single Leader Replication

Sabse easy solution.

---

Architecture

```
          Leader

        /    |     \

Follower F1

Follower F2

Follower F3
```

---

Saare writes

Leader ke paas.

---

Leader kya karta hai?

Ek

# Replication Log

banata hai.

---

Example

```
Log

1.

Insert User

2.

Update Balance

3.

Delete Order

4.

Leader=B
```

---

Followers

Same order me apply karte hain.

```
1

↓

2

↓

3

↓

4
```

Sabka order identical.

---

# Real Life Example 📖

Teacher notebook me attendance likh raha hai.

```
Roll1

↓

Roll2

↓

Roll3
```

Sab teachers same notebook follow karenge.

Nobody changes order.

---

# Advantage

Very easy.

Order already fixed.

---

# Problem

Leader hi bottleneck hai.

Leader crash?

Problem.

---

# Multi-Leader Systems 😭

Ab imagine

```
Node A

↓

Write
```

Aur

```
Node B

↓

Write
```

Same time.

Ab order kaise decide karoge?

---

Example

Node A

```
Balance=100
```

Node B

```
Balance=200
```

Both at same time.

Kaunsa latest?

Nobody knows.

---

Need

# Ordering Mechanism

---

# Solution 1

# Version Vectors

---

Har node apna counter maintain karega.

Example

```
A

↓

5
```

```
B

↓

8
```

Version

```
(A=5,B=8)
```

---

Ye batata hai

kis node ne kitni writes ki.

---

# Example

Initial

```
(A=0,B=0)
```

A writes

```
(A=1,B=0)
```

---

B writes

```
(A=1,B=1)
```

---

A writes

```
(A=2,B=1)
```

---

Current version

```
(A=2,B=1)
```

---

# Why Useful?

Hum compare kar sakte hain.

Kaunsi update newer hai.

---

# Problem 😭

Suppose

100 nodes.

Version vector

```
(N1=5)

(N2=8)

(N3=10)

...

(N100=99)
```

Storage

```
O(N)
```

Bahut bada.

---

# Solution 2

# Lamport Clock ⭐

Interview Favourite.

---

## Idea

Har node ke paas sirf

```
1 Counter
```

Bas.

---

Example

```
Node A

Clock=5
```

```
Node B

Clock=8
```

---

# Rule 1

Har local event pe

```
Clock++
```

---

Example

```
Clock=5

↓

Write

↓

Clock=6
```

---

# Rule 2

Message bhejte waqt

Clock bhi bhejo.

```
Write

Timestamp=6
```

---

# Rule 3 (Most Important)

Message receive hua.

Formula

```
New Clock

=

Max(Local Clock,

Incoming Clock)

+1
```

---

# Example

Node A

```
Clock=5
```

Node B

```
Clock=10
```

B sends

```
10
```

A receives.

Formula

```
Max(5,10)+1

=

11
```

Now

```
A=11
```

---

# Another Example

Client

```
Clock=20
```

Node

```
Clock=15
```

Formula

```
Max(20,15)+1

=

21
```

Done.

---

# Why +1 ?

Taaki new event hamesha previous event se bada ho.

Sequence kabhi break na ho.

---

# Real Life Example 📦

Courier tracking.

Package reaches

Delhi

```
Event=5
```

Mumbai receives.

Already

```
Event=8
```

New event

```
9
```

Never

```
6
```

Otherwise history ulat jayegi.

---

# Lamport Gives

✅ Total Ordering

---

Meaning

Har event ka ek order ban jayega.

Example

```
Event1

↓

Event2

↓

Event3

↓

Event4
```

---

# But Wait...

Ye Linearizability guarantee nahi karta.

😱

---

# WHY?

Sabse important concept.

---

Suppose

Node A

```
Write

Leader=B
```

Clock

```
100
```

---

Replication abhi Node B tak nahi pahuchi.

Network slow.

---

Client B read karta hai.

Node B bolta

```
Leader=A
```

Purana data.

---

Question

Lamport timestamp tha?

YES.

---

Latest order pata tha?

YES.

---

Phir bhi wrong read mila?

YES.

---

Why?

Because

```
Ordering

≠

Replication Complete
```

Ye bahut important interview point hai.

---

# Memory Trick 🧠

```
Lamport

↓

Knows

WHO came later

```

But

```
Does NOT know

Whether everyone has seen it.
```

---

# Read After Write Problem

Suppose

```
Write

↓

Success
```

Immediately

```
Read
```

Expected

```
Latest Value
```

Actual

```
Old Value
```

Ye hi

# Read After Write Inconsistency

---

# Multi Leader Problem

Example

```
Node A

↓

Write X
```

Node B

Still doesn't know.

Client reads B.

Gets

Old value.

---

# Single Leader Problem

Leader

```
Write Success
```

Leader crashes.

Replication nahi hui.

Follower becomes leader.

Follower ke paas

Old Data.

Read

↓

Old Value.

Again

Not Linearizable.

---

# Timeline Example 🎯

```
Leader

↓

Write Balance=500

↓

Crash

↓

Follower promoted

↓

Follower never got update

↓

Client Reads

↓

Balance=1000
```

Wrong.

---

# Solution?

Need something stronger.

---

# Total Order Broadcast

Sab machines

Same writes

Same order

Same time.

---

# Distributed Consensus

Machines agree.

```
Leader

↓

Followers

↓

Agreement
```

Only then commit.

---

Protocols

```
Raft

Paxos

ZAB
```

Ye ensure karte hain

Everyone agrees.

---

# Real Life Example 🗳️

Imagine election.

5 judges.

Winner tabhi announce hoga

jab majority agree kare.

Na ki ek judge bol de.

Exactly same.

---

# Why Consensus Needed?

Without consensus

Different machines

Different truth.

---

Consensus says

```
One Truth

For Everyone
```

---

# Interview Questions 🎤

---

## Why Isn't Lamport Enough?

Because

It only orders events.

It does NOT guarantee latest write is visible everywhere.

---

## Difference Between Ordering And Linearizability?

Ordering

```
Knows sequence.
```

Linearizability

```
Guarantees latest completed write is returned.
```

---

## Why Single Leader Isn't Always Linearizable?

Leader crash before replication.

Follower becomes leader.

Latest write lost.

---

## Why Multi-Leader Difficult?

Concurrent writes create conflicts.

Need ordering.

Need consensus.

---

## What Does Replication Log Do?

Stores all writes in one sequence.

Followers replay exactly same order.

---

# Advantages Of Linearizable Storage ✅

✔ Strong consistency

✔ Correct reads

✔ No stale data

✔ Easier application logic

✔ Great for banking, payments, metadata

---

# Disadvantages ❌

❌ Higher latency

❌ Needs coordination

❌ Hard to scale globally

❌ Consensus protocols are expensive

---

# Where Is Linearizability Required?

### Banking 💰

Latest balance should always be correct.

---

### Payment Gateway 💳

Double payment avoid karna.

---

### Leader Election 👑

Everyone should know same leader.

---

### Inventory System 📦

Stock should never become negative.

---

### Lock Services 🔒

Distributed locks require strict ordering.

---

# Where Eventual Consistency Is Enough?

- Instagram likes ❤️
- YouTube views ▶️
- Twitter/X follower count 🐦
- Product recommendations 🛍️

Agar 2-3 second late update hua to koi problem nahi.

---

# Cheat Sheet 📌

```
Goal
====
Latest write should always be visible.

Linearizability
===============
Completed write
↓

Future reads
↓

Latest value.

Single Leader
=============
Replication Log
Sequential writes.

Multi Leader
============
Concurrent writes.

Need ordering.

Version Vector
==============
Stores counter of every node.

Space = O(N)

Lamport Clock
=============
One counter per node.

Formula
=======
New Clock

=

Max(Local,

Incoming)+1

Pros
====
✔ Constant Space
✔ Total Ordering

Cons
====
❌ Doesn't guarantee Linearizability.

Need
====
Consensus

Protocols
=========
Raft
Paxos
ZAB
```

---

# Final Intuition 🎯

Imagine ek **Google Doc** hai jise 100 log edit kar rahe hain. 📝

- Agar **har kisi ko latest edit turant dikh jaye**, aur koi bhi purana version kabhi na dekhe → **Linearizable Storage** ✅
- Agar system sirf ye jaanta ho ki *kis edit ka order kya tha*, lekin kuch users ko abhi bhi purana version dikh raha ho → **Lamport Clock (Ordering hai, visibility guarantee nahi)** ⚠️
- Agar sab computers pe decide hi na ho paaye ki latest edit kaunsa hai → **Consensus ki zarurat hai (Raft/Paxos)** 🤝

---

# 🧠 30 Second Revision

```
Problem
=======
Need latest data on every read.

Linearizability
===============
Completed write
↓

Every future read sees latest value.

Single Leader
=============
Easy ordering using Replication Log.

Multi Leader
============
Concurrent writes.

Need ordering.

Version Vector
==============
Counter for every node.

O(N) space.

Lamport Clock
=============
One counter.

Formula:
Max(Local, Incoming)+1

Gives:
✔ Total Order

Does NOT Give:
❌ Linearizability

Reason:
Replication delay.

Final Solution
==============
Distributed Consensus

↓

Raft

↓

Paxos

↓

Total Order Broadcast
```

> 💡 **Golden Interview Line:**  
> **"Lamport Clocks provide a total ordering of events, but they do not guarantee linearizability because ordering an event is different from ensuring that every replica has applied and exposed that event to future reads."**