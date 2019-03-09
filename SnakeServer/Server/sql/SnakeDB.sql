CREATE TABLE IF NOT EXISTS items(
    id int NOT NULL AUTO_INCREMENT,
    type int NOT NULL,
    data BLOB NOT NULL,

    PRIMARY KEY(id)
);

CREATE TABLE IF NOT EXISTS players(
    id int NOT NULL AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
	gmail VARCHAR(64) NOT NLLL,
	money int NOT NULL DEFAULT 0,
	avgrecord int NOT NULL DEFAULT 0,
	record int NOT NULL DEFAULT 0,
	lastOnline date not null DEFAULT 0,
	onlinetime int not null DEFAULT 0,
	currentsnake int not null DEFAULT 0,

    PRIMARY KEY(id),

    FOREIGN KEY(currentsnake) REFERENCES items(id)
        ON UPDATE CASCADE
        ON DELETE CASCADE

);

CREATE TABLE IF NOT EXISTS ovners(
	player int NOT NULL,
	item int NOT NULL

    FOREIGN KEY(player) REFERENCES players(id)
        ON UPDATE CASCADE
        ON DELETE CASCADE

    FOREIGN KEY(item) REFERENCES items(id)
        ON UPDATE CASCADE
        ON DELETE CASCADE
);

CREATE UNIQUE INDEX IF NOT EXISTS iovners ON ovners(player,item);
