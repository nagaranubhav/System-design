# 🚀 Raft Consensus Algorithm - Leader Election (The Heart ❤️ of Distributed Systems)

> ## 🎯 One Line Definition
>
> **Raft** ek **Distributed Consensus Algorithm** hai jo ensure karta hai ki multiple machines (nodes) ek hi decision par agree karein.
>
> Iska main goal:
>
> - ✅ Ek hi Leader ho
> - ✅ Sab logs same order me ho
> - ✅ Data linearizable ho
> - ✅ Failures ke baad bhi system continue kare
>
> 💡 **Simple Language**
>
> > **"Raft ka kaam hai sab computers ko ek hi sach (truth) par agree karwana."**

---

# 🤔 Sabse Pehle Problem Samjho

Suppose tumhare paas ek distributed database hai.

```
        Node A

        Node B

        Node C

        Node D

        Node E
```

Sabke paas data ki copy hai.

Question:

```
Write request kis node pe jayegi?
```

Agar sab nodes likhne lagen...

```
A -> Balance = 100

B -> Balance = 500

C -> Balance = 200
```

😂😂😂

Sabka data alag ho jayega.

Chaos.

---

# Solution?

Ek hi banda decision lega.

Usko bolte hain

# 👑 Leader

Baaki

```
Followers
```

banenge.

Architecture

```
                Leader

          /      |      \

      Follower Follower Follower
```

Saare writes

```
↓

Leader

↓

Followers
```

Bas.

---

# Real Life Example 👨‍🏫

Class me teacher attendance le raha hai.

Students khud attendance nahi likhte.

```
Teacher

↓

Attendance Register

↓

Students
```

Teacher = Leader

Students = Followers

---

# Why Consensus Needed?

Imagine WhatsApp group.

5 admins.

Sab simultaneously group icon change kar rahe.

😂

Final icon kaunsa hoga?

Nobody knows.

Consensus

↓

Ek admin choose karo.

Problem solved.

---

# Raft's Main Goal 🎯

Raft actually 3 major problems solve karta hai.

```
1.

Leader Election

↓

2.

Log Replication

↓

3.

Safety
```

Ye video mainly

# Leader Election

cover karti hai.

---

# Important Terminologies 📖

---

# 1. Node

Server.

Simple.

---

# 2. Leader

Only node allowed to accept writes.

---

# 3. Follower

Leader ki commands execute karta hai.

Khud decision nahi leta.

---

# 4. Candidate

Election ke time temporary role.

```
Follower

↓

Timeout

↓

Candidate

↓

Wins

↓

Leader
```

---

# 5. Term ⭐⭐⭐

Most Important Interview Concept.

---

## Term Kya Hai?

Term = Election Number

Har election ka unique number.

Example

```
Election1

↓

Term 1

Election2

↓

Term 2

Election3

↓

Term 3
```

Simple.

---

# Think Like IPL Seasons 🏏

```
IPL 2024

↓

Season Number

IPL 2025

↓

New Season

IPL 2026

↓

New Season
```

Exactly same.

Term batata hai

```
Current leadership generation
```

---

# Why Need Term?

Suppose

Old Leader

```
Term = 20
```

New election

```
Leader

Term = 21
```

Agar purana leader wapas aa gaya.

Kaise pata chalega

ki

old hai?

Term.

Higher term

↓

New leader.

Lower term

↓

Old leader.

---

# Memory Trick

Think

```
Term

=

Version Number
```

Higher version

Always newer.

---

# Complete Node State Machine

```
          +------------+
          | Follower   |
          +------------+
                 |
       Timeout (No Heartbeat)
                 |
                 V
          +------------+
          | Candidate  |
          +------------+
                 |
        Majority Votes?
         /            \
       Yes             No
        |              |
        V              |
   +------------+      |
   |  Leader    |<-----+
   +------------+
        |
 Leader Crash / Higher Term Seen
        |
        V
   Back to Follower
```

Ye pura Raft isi state machine ke around ghoomta hai.

---

# Heartbeats ❤️

Leader ko followers ko continuously batana padta hai

```
Main zinda hu.
```

Ye message

```
Heartbeat
```

kehlata hai.

Example

Every

```
100 ms
```

Leader sends

```
PING
```

---

Follower

```
Heartbeat received

↓

Everything OK
```

---

# Real Life Example 📱

WhatsApp

```
Last Seen

Online

Typing...
```

Ye signals batate hain banda active hai.

Heartbeats bhi same.

---

# Why Heartbeats Needed?

Agar leader chup ho gaya.

Followers ko kaise pata chalega

Leader mar gaya?

Heartbeats.

---

Timeline

```
Leader

↓

Heartbeat

↓

Heartbeat

↓

Heartbeat

↓

(No heartbeat)

↓

Follower suspects failure
```

---

# Election Timeout ⭐⭐⭐

Ye interview favourite hai.

---

Follower continuously timer chala raha hota hai.

```
150 ms

↓

200 ms

↓

250 ms
```

Heartbeat aa gaya?

```
YES

↓

Reset Timer
```

---

Heartbeat nahi aaya?

```
Timeout
```

Election start.

---

# Why Random Timeout?

Suppose

5 followers.

Sabka timeout

```
200ms
```

Ek saath timeout.

Sab ban gaye

Candidate.

😂

Sab vote maangenge.

Nobody wins.

---

Instead

Random

```
Node1

170ms

Node2

250ms

Node3

190ms

Node4

300ms

Node5

220ms
```

Ab

Node1 pehle timeout karega.

Election start.

Baaki usko vote de denge.

---

# Visualization

Without Random Timeout

```
All Timeout Together

↓

5 Candidates

↓

Split Votes

↓

No Leader
```

---

With Random Timeout

```
Node2 Timeout First

↓

Candidate

↓

Gets Votes

↓

Leader
```

Much better.

---

# Candidate Phase

Follower timeout.

Ab

```
Follower

↓

Candidate
```

Candidate kya karta hai?

---

## Step 1

Term increase.

Example

```
Current Term

28
```

Candidate

```
Term=29
```

---

## Step 2

Vote khud ko.

```
Votes=1
```

Always.

---

## Step 3

Sabko message bhejta hai.

```
Vote For Me

Term=29
```

Is message ko bolte hain

```
RequestVote RPC
```

---

Architecture

```
         Candidate

      /     |      \

Vote? Vote? Vote?
```

---

# Voting Rules ⭐⭐⭐⭐⭐

Ye bahut important hai.

---

## Rule 1

One Node

One Vote

Per Term.

Example

```
Term 25

↓

Already voted

↓

Cannot vote again.
```

---

Why?

Otherwise

Same node

2 candidates ko vote de dega.

2 leaders ban jayenge.

Impossible.

---

## Rule 2

Higher Term Always Wins

Suppose

Leader

```
Term=20
```

Candidate

```
Term=21
```

Leader receives request.

Immediately

Leader

↓

Follower.

---

Why?

Because

Candidate newer generation ka hai.

---

# Real Life Example

Company

CEO Version 2025

New CEO appointed

2026

Purana CEO office nahi chala sakta.

😂

---

## Rule 3 (Most Important)

Candidate ka log

Follower se

at least

utna updated hona chahiye.

---

# Why This Rule Exists?

Interview Gold ⭐⭐⭐⭐⭐

Suppose

Follower

```
Logs

1

2

3

4

5
```

Candidate

```
Logs

1

2
```

Candidate old hai.

Agar ye leader ban gaya.

Latest logs

```
3

4

5
```

Lost.

Data corruption.

---

Hence

Follower bolega

```
Sorry.

Tumhare paas mera latest data hi nahi hai.

Vote nahi dunga.
```

---

# Up-to-date Log Rule

Follower compares

```
Candidate Last Log Term

AND

Candidate Last Log Index
```

with

its own.

Agar candidate newer hai

Vote.

Else

Reject.

---

# Real Life Example 📚

School monitor election.

Ek student

Saare class notes rakhta hai.

Dusra

Half notebook kho chuka hai.

Teacher monitor kise banayega?

Obviously

Full notebook wale ko.

---

# Quorum ⭐⭐⭐⭐⭐

Most asked interview concept.

---

## Quorum Kya Hai?

Simple.

```
Majority.
```

Formula

```
N/2 +1
```

---

Examples

```
3 Nodes

↓

2 Votes
```

---

```
5 Nodes

↓

3 Votes
```

---

```
7 Nodes

↓

4 Votes
```

---

# Why Majority?

Imagine

5 nodes.

Leader1 gets

```
3 votes
```

Leader2

```
3 votes
```

Possible?

NO.

Impossible.

Because

```
Majorities always overlap.
```

Ye hi Raft ki safety ka foundation hai.

---

# Split Brain Problem

Imagine

2 leaders.

Leader A

```
Balance=100
```

Leader B

```
Balance=500
```

😂😂

Bank band.

---

Raft prevents this.

Using

```
Majority
```

---

# Why Two Leaders Cannot Exist?

Suppose

5 nodes.

Leader A

needs

```
3 votes
```

Leader B

also needs

```
3 votes
```

Total

```
6 votes
```

But

Nodes

Only

```
5
```

Impossible.

At least one node common hoga.

Aur ek node

same term me

2 votes nahi de sakta.

Hence

```
One Leader Only.
```

Interview me ye explanation bolna.

---

# Leader Demotion ⭐⭐⭐

Suppose

Old Leader

```
Term=15
```

Network issue hua.

Election hua.

New Leader

```
Term=16
```

Old leader wapas aya.

Usne dekha

```
Higher Term.
```

Immediately

```
Leader

↓

Follower
```

---

Why?

Higher term always newer.

---

# Fencing Tokens ⭐⭐⭐⭐⭐

One of the most important interview topics.

---

## Problem

Old leader network partition me tha.

Usko laga

```
Main leader hu.
```

Meanwhile

New leader ban gaya.

Old leader returns.

Ab?

---

Solution

Terms act as

# Fencing Tokens

---

Example

Old Leader

```
Term=20
```

New Leader

```
Term=21
```

Old leader tries write.

Storage checks.

```
Incoming Term

20

Current

21
```

Reject.

Simple.

---

# Real Life Example 🏢

Office access card.

Old employee card

```
Version=10
```

Company issued

New card

```
Version=11
```

Old card

Automatically invalid.

Exactly fencing.

---

# Backfilling ⭐⭐⭐⭐

Suppose

Follower was offline.

Leader continued writing logs.

Leader

```
1

2

3

4

5

6

7
```

Follower

```
1

2

3
```

Poor guy behind. 😭

---

Leader sends

```
4

5

6

7
```

Follower catches up.

This process

↓

Backfilling.

---

# Visualization

```
Leader

1

2

3

4

5

6

7

↓

Follower

1

2

3

↓

Leader sends

4

5

6

7

↓

Follower Updated

1

2

3

4

5

6

7
```

---

# Complete Leader Election Flow 🎯

```
Leader Alive

↓

Heartbeats

↓

Follower Happy

↓

Leader Dies

↓

Heartbeat Stops

↓

Random Timeout

↓

Follower

↓

Candidate

↓

Term++

↓

Vote Self

↓

RequestVote RPC

↓

Majority?

↓

YES

↓

Leader

↓

Starts Heartbeats
```

---

# Failure Scenarios 🚨

## Scenario 1

Leader crashes.

```
Heartbeat stops

↓

Election

↓

New Leader
```

---

## Scenario 2

Candidate loses election.

```
No Majority

↓

Wait

↓

New Timeout

↓

Retry
```

---

## Scenario 3

Old leader returns.

```
Higher Term Seen

↓

Become Follower
```

---

## Scenario 4

Follower offline.

```
Missed Logs

↓

Backfill
```

---

# Why Raft Is Easier Than Paxos?

Paxos

```
Mathematically elegant

But

Very difficult.
```

Raft

```
Leader based

↓

Simple

↓

Easy to implement

↓

Easy to reason about
```

Isi liye industry me Raft bahut popular hai.

---

# Where Is Raft Used?

- **etcd** (Kubernetes ka brain 🧠)
- **Consul**
- **TiKV**
- **CockroachDB** (Raft-based replication)
- **RethinkDB**
- **Nomad**

---

# Interview Questions 🎤

---

## Why Random Timeout?

To avoid split votes.

---

## Why Heartbeats?

Followers ko batane ke liye ki leader alive hai.

---

## Why Candidate Votes for Itself?

Election fast ho jaye.

---

## Why Higher Term Wins?

Higher term means newer election.

---

## Why Up-to-date Log Check?

Outdated node kabhi leader nahi ban sakta.

Otherwise latest committed data lose ho sakta hai.

---

## Why Majority?

Guarantees only one leader.

---

## Why Can't Two Leaders Exist?

One node cannot vote twice in same term.

Majorities always overlap.

---

## What Is Fencing?

Reject stale leader writes using term numbers.

---

## What Is Backfilling?

Leader stale followers ko missing logs bhejkar sync karta hai.

---

# Cheat Sheet 📌

```
Raft
====
Consensus Algorithm

Goal
====
✔ One Leader
✔ Same Log Order
✔ Linearizability

Roles
=====
Follower
Candidate
Leader

Term
====
Election Number

Heartbeat
=========
Leader Alive Signal

Election
========
No Heartbeat
↓

Timeout
↓

Candidate

RequestVote RPC
===============
Candidate asks votes.

Vote Rules
==========
✔ One vote per term
✔ Higher term wins
✔ Candidate log must be up-to-date

Quorum
======
N/2 + 1

Leader Demotion
===============
Higher term seen
↓

Become follower

Fencing
========
Old term writes rejected.

Backfilling
===========
Leader syncs stale followers.

Used In
=======
etcd
Consul
CockroachDB
TiKV
```

---

# 🧠 Interview Deep Dive (Most Important Concepts)

## ⭐ 1. Why "Up-to-date Log" Rule Is Mandatory?

Ye Raft ka sabse important safety rule hai.

### Imagine:

```
Leader Logs

Index : 1 2 3 4 5 6 7

Follower A

1 2 3 4 5 6 7

Follower B

1 2 3
```

Leader crash ho gaya.

Election start.

Agar **Follower B** leader ban gaya to?

Uske paas sirf

```
1 2 3
```

hai.

Wo bolega

```
Mere logs hi correct hain.
```

Ab

```
4 5 6 7
```

ka kya?

Gone forever.

❌ Data Loss.

Isliye follower vote dene se pehle check karta hai:

```
Candidate ka last log
>=
Mere last log
```

Tabhi vote.

---

## ⭐ 2. Why Majority Guarantees Safety?

Ye question almost har System Design interview me aa sakta hai.

Suppose 5 nodes hain.

```
A B C D E
```

Leader banne ke liye chahiye

```
3 votes
```

Assume Candidate X gets

```
A B C
```

Candidate Y ko bhi leader banna hai.

Usko bhi chahiye

```
3 votes
```

Lekin bache kaun?

```
D E
```

Sirf 2.

Impossible.

Aur agar Y ne

```
C D E
```

liye, to node **C** ko same term me do baar vote dena padega, jo allowed hi nahi.

Hence **same term me ek hi leader possible hai.**

---

## ⭐ 3. Why Terms Are Called Fencing Tokens?

Interview me ye line bol dena:

> **"Term acts like a lease/version number. Any request carrying an older term is automatically rejected, preventing an old leader from corrupting the system."**

Yehi fencing hai.

---

# 🎯 Final Intuition

Imagine ek school hai. 🏫

- **Principal = Leader**
- **Teachers = Followers**
- **Election Year = Term**
- **Attendance Register = Log**
- **Morning Assembly = Heartbeat**
- **Voting = Quorum**
- **Old Principal's Expired ID Card = Fencing Token**

Jab tak principal roz assembly leta rahe (heartbeat), sabko pata hai school normal chal raha hai.

Agar principal aana band kar de:

- Teachers wait karte hain (random timeout)
- Ek teacher election call karta hai (candidate)
- Majority usko vote deti hai (quorum)
- Wo naya principal ban jata hai (leader)
- Purana principal agar baad me aa bhi jaye aur uske paas purana ID card (old term) ho, to uski authority reject ho jati hai (fencing).

💡 **Raft ka essence:**

> **"Ek hi leader, majority ka support, ordered logs aur stale leaders ki no-entry — isi combination se distributed systems consistent aur fault tolerant bante hain."**