CREATE TABLE "Account" (
	"Account_id"	INTEGER NOT NULL UNIQUE,
	"Account_balance"	INTEGER NOT NULL,
	"Account_transactions"	BLOB,
	"Account_branch"	TEXT,
	"Account_active"	TEXT NOT NULL DEFAULT 'DEACTIVE',
	FOREIGN KEY("Account_branch") REFERENCES "Branch"("Branch_id") ON UPDATE CASCADE,
	PRIMARY KEY("Account_id")
);

CREATE TABLE "Branch" (
	"Branch_id"	TEXT NOT NULL UNIQUE,
	"Branch_name"	TEXT NOT NULL,
	"Branch_city"	TEXT NOT NULL,
	"Branch_address"	TEXT NOT NULL,
	"Branch_active"	TEXT NOT NULL DEFAULT 'INACTIVE',
	"Branch_manager"	TEXT,
	PRIMARY KEY("Branch_id"),
	FOREIGN KEY("Branch_manager") REFERENCES "Employee"("Employee_id")
);

CREATE TABLE "Customer" (
	"Customer_id"	TEXT NOT NULL UNIQUE,
	"Customer_name"	TEXT NOT NULL,
	"Customer_password"	TEXT NOT NULL,
	"Customer_account"	INTEGER NOT NULL,
	"Customer_address"	TEXT,
	"Customer_branch"	TEXT NOT NULL DEFAULT 'DEL-BRANCH',
	FOREIGN KEY("Customer_branch") REFERENCES "Branch"("Branch_id") ON UPDATE CASCADE,
	FOREIGN KEY("Customer_account") REFERENCES "Account"("Account_id"),
	CONSTRAINT "pkey" PRIMARY KEY("Customer_id")
	CHECK (LENGTH("Employee_password") > 0)
);

CREATE TABLE "Employee" (
    "Employee_id" TEXT NOT NULL UNIQUE,
    "Employee_name" TEXT NOT NULL,
    "Employee_password" TEXT NOT NULL,
    "Employee_designation" TEXT NOT NULL,
    "Employee_address" TEXT NOT NULL,
    PRIMARY KEY ("Employee_id")
	CHECK (LENGTH("Employee_password") > 0)
);

CREATE TABLE "EmployeeToBranch" (
    "Employee_id" TEXT NOT NULL,
    "Branch_id" TEXT NOT NULL,
    PRIMARY KEY ("Employee_id", "Branch_id"),
    FOREIGN KEY ("Employee_id") REFERENCES "Employee" ("Employee_id") ON UPDATE CASCADE,
    FOREIGN KEY ("Branch_id") REFERENCES "Branch" ("Branch_id") ON UPDATE CASCADE
);