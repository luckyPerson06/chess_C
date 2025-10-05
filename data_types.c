


typedef enum { COLOR_WHITE, COLOR_BLACK, COLOR_NONE } PIECE_COLOR;
typedef enum { PT_PAWN, PT_ROOK, PT_KNIGHT, PT_BISHOP, PT_QUEEN, PT_KING, PT_NONE } PIECE_TYPE;



typedef struct
{

    PIECE_TYPE type;
    PIECE_COLOR color;
    int has_moved;
    int under_attack;

} PIECE;