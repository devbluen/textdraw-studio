
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
        invert INTEGER DEFAULT 0, \
        PRIMARY KEY(id), \
        CONSTRAINT textdraws_project_id_projects_id FOREIGN KEY(project_id) REFERENCES projects(id) ON DELETE CASCADE ON UPDATE CASCADE \
    )"

#define eTableTrash \
    "CREATE TABLE IF NOT EXISTS trash ( \
        id INTEGER PRIMARY KEY AUTOINCREMENT, \
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
        invert INTEGER DEFAULT 0, \
        CONSTRAINT trash_project_id_projects_id FOREIGN KEY(project_id) REFERENCES projects(id) ON DELETE CASCADE ON UPDATE CASCADE \
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

#define eTableUndoSteps \
    "CREATE TABLE IF NOT EXISTS undo_steps ( \
        id INTEGER PRIMARY KEY AUTOINCREMENT, \
        project_id INTEGER NOT NULL, \
        CONSTRAINT undo_steps_project_id_projects_id FOREIGN KEY(project_id) REFERENCES projects(id) ON DELETE CASCADE ON UPDATE CASCADE \
    )"

#define eTableUndoTextdraws \
    "CREATE TABLE IF NOT EXISTS undo_textdraws ( \
        step_id INTEGER NOT NULL, \
        id INTEGER, \
        project_id INTEGER, \
        position TEXT, \
        size TEXT, \
        letter_size TEXT, \
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
        model_rotation TEXT, \
        model_colors TEXT, \
        box INTEGER DEFAULT 0, \
        variable TEXT, \
        invert INTEGER DEFAULT 0, \
        CONSTRAINT undo_textdraws_step_id_undo_steps_id FOREIGN KEY(step_id) REFERENCES undo_steps(id) ON DELETE CASCADE ON UPDATE CASCADE \
    )"

#define eTableUndoGroups \
    "CREATE TABLE IF NOT EXISTS undo_groups ( \
        step_id INTEGER NOT NULL, \
        id INTEGER, \
        project_id INTEGER, \
        name TEXT, \
        indexGroup INTEGER, \
        CONSTRAINT undo_groups_step_id_undo_steps_id FOREIGN KEY(step_id) REFERENCES undo_steps(id) ON DELETE CASCADE ON UPDATE CASCADE \
    )"

#define eTableUndoGroupsTextDraws \
    "CREATE TABLE IF NOT EXISTS undo_groups_textdraws ( \
        step_id INTEGER NOT NULL, \
        draw_id INTEGER, \
        group_id INTEGER, \
        CONSTRAINT undo_groups_textdraws_step_id_undo_steps_id FOREIGN KEY(step_id) REFERENCES undo_steps(id) ON DELETE CASCADE ON UPDATE CASCADE \
    )"

#define eTableUndoTrash \
    "CREATE TABLE IF NOT EXISTS undo_trash ( \
        step_id INTEGER NOT NULL, \
        project_id INTEGER, \
        position TEXT, \
        size TEXT, \
        letter_size TEXT, \
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
        model_rotation TEXT, \
        model_colors TEXT, \
        box INTEGER DEFAULT 0, \
        variable TEXT, \
        invert INTEGER DEFAULT 0, \
        CONSTRAINT undo_trash_step_id_undo_steps_id FOREIGN KEY(step_id) REFERENCES undo_steps(id) ON DELETE CASCADE ON UPDATE CASCADE \
    )"

#define eIndexTrashProject       "CREATE INDEX IF NOT EXISTS idx_trash_project ON trash(project_id)"
#define eIndexUndoStepsProject   "CREATE INDEX IF NOT EXISTS idx_undo_steps_project ON undo_steps(project_id)"
#define eIndexUndoTextdrawsStep  "CREATE INDEX IF NOT EXISTS idx_undo_textdraws_step ON undo_textdraws(step_id)"
#define eIndexUndoGroupsStep     "CREATE INDEX IF NOT EXISTS idx_undo_groups_step ON undo_groups(step_id)"
#define eIndexUndoGroupsTextStep "CREATE INDEX IF NOT EXISTS idx_undo_groups_textdraws_step ON undo_groups_textdraws(step_id)"
#define eIndexUndoTrashStep      "CREATE INDEX IF NOT EXISTS idx_undo_trash_step ON undo_trash(step_id)"

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

#define eTableUserLanguage \
    "CREATE TABLE IF NOT EXISTS user_language ( \
        name TEXT NOT NULL, \
        language INTEGER NOT NULL DEFAULT 1, \
        PRIMARY KEY (name) \
    )"