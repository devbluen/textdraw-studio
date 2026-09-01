
#define eTableProjects \
    "CREATE TABLE projects ( \
        id INTEGER, \
        name TEXT NOT NULL, \
        date TEXT NOT NULL, \
        globalVariable TEXT DEFAULT 'TSGlobal', \
        playerVariable TEXT DEFAULT 'TSPlayer', \
        PRIMARY KEY(id) \
    )"

#define eTableTextdraws \
    "CREATE TABLE IF NOT EXISTS textdraws ( \
        id INTEGER, \
        project_id INTEGER, \
        position TEXT DEFAULT '0.0,0.0', \
        size TEXT DEFAULT '0.0,0.0', \
        letter_size TEXT DEFAULT '0.0,0.0', \
        text TEXT, \
        font INTEGER, \
        align INTEGER, \
        proportion INTEGER, \
        outline INTEGER, \
        shadow INTEGER, \
        color INTEGER, \
        colorBackground INTEGER, \
        colorBox INTEGER, \
        selectable INTEGER, \
        mode INTEGER, \
        indexDraw INTEGER, \
        itemType INTEGER DEFAULT 0, \
        model INTEGER DEFAULT 1, \
        model_rotation TEXT DEFAULT '0.0,0.0,0.0,1.0', \
        model_colors TEXT DEFAULT '0,0', \
        box INTEGER DEFAULT 0, \
        variable TEXT, \
        PRIMARY KEY(id), \
        CONSTRAINT textdraws_project_id_projects_id FOREIGN KEY(project_id) REFERENCES projects(id) ON DELETE CASCADE ON UPDATE CASCADE \
    )"

#define eTableGroups \
    "CREATE TABLE groups ( \
        id INTEGER, \
        project_id INTEGER, \
        name TEXT, \
        indexGroup INTEGER, \
        PRIMARY KEY(id), \
        CONSTRAINT project_id_groups_projects_id FOREIGN KEY(project_id) REFERENCES projects(id) ON DELETE CASCADE ON UPDATE CASCADE \
    )"

#define eTableGroupsTextDraws \
    "CREATE TABLE groups_textdraws ( \
        draw_id	INTEGER, \
        group_id INTEGER, \
        CONSTRAINT groups_textdraws_id_textdraws_id FOREIGN KEY(draw_id) REFERENCES textdraws(id) ON DELETE CASCADE ON UPDATE CASCADE, \
        CONSTRAINT groups_id_textdraws_id FOREIGN KEY(group_id) REFERENCES groups(id) ON DELETE CASCADE ON UPDATE CASCADE \
    )"

#define eTableSprites \
    "CREATE TABLE sprites ( \
        id INTEGER, \
        type INTEGER, \
        sprite TEXT UNIQUE, \
        PRIMARY KEY(id) \
    )"

#define eTableSpritesFavorites \
    "CREATE TABLE sprites_favorites ( \
        user TEXT, \
        sprite_id INTEGER, \
        CONSTRAINT sprites_favorites_sprite_id_sprites_id FOREIGN KEY(sprite_id) REFERENCES sprites(id) ON DELETE CASCADE ON UPDATE CASCADE \
    )"

#define eTablesColors \
    "CREATE TABLE IF NOT EXISTS colors ( \
        id INTEGER NOT NULL, \
        name TEXT NULL, \
        color INTEGER NULL, \
        PRIMARY KEY (id) \
    )"