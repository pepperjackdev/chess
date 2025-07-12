package me.pepperjackdev.chess.io;

import me.pepperjackdev.chess.core.data.state.placement.Placement;
import me.pepperjackdev.chess.core.piece.Piece;
import me.pepperjackdev.chess.core.position.Position;

import java.util.Optional;

public class PlacementConverter {
    public static String serialize(Placement placement) {
        StringBuilder placementStringBuilder = new StringBuilder();

        int emptyCols = 0;
        for (int row = placement.getSize().rows() - 1; row >= 0; row--) {
            if (row != placement.getSize().rows() - 1) placementStringBuilder.append('/');
            for (int col = 0; col < placement.getSize().columns(); col++) {
                Optional<Piece> optionalPiece = placement.getPiece(new Position(row, col));
                if (optionalPiece.isPresent()) {
                    if (emptyCols > 0) {
                        placementStringBuilder.append(emptyCols);
                        emptyCols = 0;
                    }
                    placementStringBuilder.append(optionalPiece.get());
                } else {
                    emptyCols++;
                }
            }

            if (emptyCols > 0) {
                placementStringBuilder.append(emptyCols);
                emptyCols = 0;
            }
        }

        return placementStringBuilder.toString();
    }

    public static Placement deserialize(String placement) {
        throw new UnsupportedOperationException("Not supported yet.");
    }
}
