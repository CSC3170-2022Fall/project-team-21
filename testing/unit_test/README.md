# Unit Test

This is a simple framework for unit test. The components in test.h are modified from 
[MyTinySTL](https://github.com/Alinshans/MyTinySTL/blob/master/Test/test.h)

## Output
- Row test:  <br>
  ![row_test](../../presentation/images/row_test.jpg) <br>
- SchemaItem test:  <br>
  ![schemaitem_test](../../presentation/images/schemaitem_test.jpg) <br>
- Table test:  <br>
  ![table_test](../../presentation/images/table_test.jpg) <br>
- Database test:  <br>
  ![database_test](../../presentation/images/database_test.jpg) <br>

## What we have tested
- [x] [Row class](Row_test.h)
  - [x] getValues
  - [x] setValues
- [x] [SchemaItem class](Schemaitem_test.h)
  - [x] getName
  - [x] getType
  - [x] getTypeFromString
- [x] [Table class](Table_test.h)
  - [x] printOut
  - [x] getRowAt
  - [x] removeRowAt
  - [x] insertLast
  - [x] insertAt
  - [x] getSize
  - [x] getSchema
  - [ ] loadFromFile
  - [ ] saveToFile
- [x] [Database class](Database_test.h)
  - [x] addTable
  - [x] getTable
  - [x] removeTableAtIdx
  - [x] removeTable
  - [ ] execute
  - [ ] saveDatabase
  - [ ] start
- [ ] CommandInterpreter class