--- A PostgreSQL Schema for Atheme 0.2
--- Copyright (c) 2005 William Pitcock, et al.
---
--- Use of this code is permitted under the terms presented in doc/LICENSE.
---
--- $Id: atheme_init.sql 1586 2005-08-10 03:52:37Z nenolod $

CREATE SEQUENCE accounts_id_seq;
CREATE SEQUENCE account_metadata_id_seq;
CREATE SEQUENCE channels_id_seq;
CREATE SEQUENCE channel_metadata_id_seq;
CREATE SEQUENCE channel_access_id_seq;
CREATE SEQUENCE channel_access_metadata_id_seq;
CREATE SEQUENCE klines_id_seq;

--- MU equivilant -- see db.c for explanation of the data structure.
CREATE TABLE ACCOUNTS
(
	ID		INT		DEFAULT nextval('accounts_id_seq')	NOT NULL,
	USERNAME	VARCHAR(255)	NOT NULL,
	PASSWORD	VARCHAR(255)	NOT NULL,
	EMAIL		VARCHAR(255)	NOT NULL,
	REGISTERED	INT		NOT NULL,
	LASTLOGIN	INT,
	FLAGS		INT,
);

CREATE TABLE ACCOUNT_METADATA
(
	ID		INT		DEFAULT nextval('account_metadata_id_seq')	NOT NULL,
	PARENT		INT		NOT NULL,
	KEYNAME		VARCHAR(255)	NOT NULL,
	VALUE		VARCHAR(255)	NOT NULL
);

--- MC equivilant
CREATE TABLE CHANNELS
(
	ID		INT		DEFAULT nextval('channels_id_seq')	NOT NULL,
	NAME		VARCHAR(255)	NOT NULL,
	FOUNDER		VARCHAR(255)	NOT NULL,
	REGISTERED	INT		NOT NULL,
	LASTUSED	INT		NOT NULL,
	FLAGS		INT		NOT NULL,
	MLOCK_ON	INT		NOT NULL,
	MLOCK_OFF	INT		NOT NULL,
	MLOCK_LIMIT	INT		NOT NULL,
	MLOCK_KEY	VARCHAR(255)	NOT NULL,
	URL		VARCHAR(255),
	ENTRYMSG	VARCHAR(255)
);

CREATE TABLE CHANNEL_METADATA
(
	ID		INT		DEFAULT nextval('channel_metadata_id_seq')	NOT NULL,
	PARENT		INT		NOT NULL,
	KEYNAME		VARCHAR(255)	NOT NULL,
	VALUE		VARCHAR(255)	NOT NULL
);

CREATE TABLE CHANNEL_ACCESS
(
	ID		INT		DEFAULT nextval('channel_access_id_seq')	NOT NULL,
	PARENT		INT		NOT NULL,
	ACCOUNT		VARCHAR(255)	NOT NULL,
	PERMISSIONS	VARCHAR(255)	NOT NULL
);

CREATE TABLE CHANNEL_ACCESS_METADATA
(
	ID		INT		DEFAULT nextval('channel_access_metadata_id_seq')	NOT NULL,
	PARENT		INT		NOT NULL,
	KEYNAME		VARCHAR(255)	NOT NULL,
	VALUE		VARCHAR(255)	NOT NULL
);

--- KL equivilant
CREATE TABLE KLINES
(
	ID		INT		DEFAULT nextval('klines_id_seq')	NOT NULL,
	USERNAME	VARCHAR(255)	NOT NULL,
	HOSTNAME	VARCHAR(255)	NOT NULL,
	DURATION	INT,
	SETTIME		INT		NOT NULL,
	SETTER		VARCHAR(255)	NOT NULL,
	REASON		VARCHAR(255)	NOT NULL
);
