- `card_api/` - "public" (for other teams) interface for querying database. It is documented in headers (`card_api/Include`) and by example (`card_api/card_api_example.cpp`)
- `db_builder/` - Database builder. Parses jsons from riot to sqlite db.
- `sqlite_helper` - Minimal internal wrapper around sqlite, used in `card_api` and `db_builder`

### Build & usage of `db_builder` and `card_api`
```
cd <project_root>
mkdir build
cd build
cmake ..
make db_builder
// download jsons from riot. This sucks. TODO: add autodownload to db_builder
curl --remote-name-all --parallel https://dd.b.pvp.net/latest/core/pl_pl/data/globals-pl_pl.json https://dd.b.pvp.net/latest/set1/pl_pl/data/set1-pl_pl.json https://dd.b.pvp.net/latest/set2/pl_pl/data/set2-pl_pl.json https://dd.b.pvp.net/latest/set3/pl_pl/data/set3-pl_pl.json https://dd.b.pvp.net/latest/set4/pl_pl/data/set4-pl_pl.json
./bin/db_builder

make card_api_example
./bin/card_api_example
```
