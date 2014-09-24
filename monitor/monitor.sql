create table config(
id integer primary key, 
name text,
label text,
port text,
baud integer,
databit integer,
stopbit integer,
pority integer,
status integer,
datatype integer,
deviceno integer,
readonly integer,
timer integer,
register integer
)

create table user(
id integer primary key, 
name text,
loginid text primary key,
pwd text,
isadmin integer,
status integer 
)

create table data(
id integer primary key,
configid integer,  
value text,
r_date text,
r_time text
)


create index idxdata on t1(configid,r_date,r_time);