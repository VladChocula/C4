// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/GridLogic/C4_GridLogicBase.h"

// Sets default values for this component's properties
UC4_GridLogicBase::UC4_GridLogicBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


int32 UC4_GridLogicBase::DropPiece(int32 Column, int32 PlayerID, AC4_Player* ScoringPlayer)
{
	// Validate board state and column
	if (BoardState != EC4BoardState::Active) return -1;
	if (Column < 0 || Column >= NumColumns) return -1;
	if (IsColumnFull(Column)) return -1;

	// Find Landings Row - walk bottom to top
	int32 LandingRow = -1;
	for (int32 Row = NumRows - 1; Row >= 0; Row--)
	{
		if (Grid[GetIndex(Row, Column)] == 0)
		{
			LandingRow = Row;
			break;
		}
	}

	if (LandingRow == -1) return -1;

	// Place the piece
	Grid[GetIndex(LandingRow, Column)] = PlayerID;

	// Begin chain resolution
	TransitionBoardState(EC4BoardState::Shifting);

	int32 RawPoints = 0;
	int32 ChainCount = 0;

	bool bFoundSequences = true;
	while (bFoundSequences)
	{
		//Find all sequences currently on the board
		TArray<TArray<int32>> AllSequences = FindAllSequences(PlayerID);

		if (AllSequences.Num() == 0)
		{
			bFoundSequences = false;
			break;
		}

		//Each sequence in this scan is its own chain event
		for (const TArray<int32>& Sequence : AllSequences)
		{
			RawPoints += ScoreSequence(Sequence);
			ChainCount++;
		}

		//Remove all found sequences from the board
		RemoveSequences(AllSequences);

		// Shift remaining pieces down
		ShiftPiecesDown();
	}

	//If anything scored, broadcast the final result
	if (ChainCount > 0)
	{
		float FinalScore = RawPoints * ChainCount;
		OnPlayerScored.Broadcast(ScoringPlayer, FinalScore);
	}

	TransitionBoardState(EC4BoardState::Active);
	return LandingRow;
}

bool UC4_GridLogicBase::IsColumnFull(int32 Column) const
{
	return Grid[GetIndex(0, Column)] != 0;
}

int32 UC4_GridLogicBase::GetIndex(int32 Row, int32 Col) const
{
	return Row * NumColumns + Col;
}

// Called when the game starts
void UC4_GridLogicBase::BeginPlay()
{
	Super::BeginPlay();

	Grid.Init(0, NumRows * NumColumns);
	
}

void UC4_GridLogicBase::TransitionBoardState(EC4BoardState NewState)
{
	EC4BoardState PreviousState = BoardState;
	BoardState = NewState;
	OnBoardStateChanged.Broadcast(PreviousState, NewState);
}

TArray<TArray<int32>> UC4_GridLogicBase::FindAllSequences(int32 PlayerID)
{
	TArray<TArray<int32>> AllSequences;
	TSet<int32> AlreadyCounted; //Prevent double counting indices

	// Direction pairs: {RowDelta, ColDelta}
	// Horizontal, Vertical, Diagonal /, Diagonal '\'
	TArray<TPair<int32, int32>> Directions = {
		{0, 1}, {1, 0}, {1, 1}, {1, -1}
	};

	for (int32 Row = 0; Row < NumRows; Row++)
	{
		for (int32 Col = 0; Col < NumColumns; Col++)
		{
			if (Grid[GetIndex(Row, Col)] != PlayerID) continue; //the piece in this index does not belong to the player

			for (const TPair<int32, int32>& Dir : Directions)
			{
				TArray<int32> Sequence;
				int32 R = Row;
				int32 C = Col;

				// Walk in direction, collect matching cells
				while (R >= 0 && R < NumRows &&
					C >= 0 && C < NumColumns &&
					Grid[GetIndex(R, C)] == PlayerID)
				{
					Sequence.Add(GetIndex(R, C));
					R += Dir.Key;
					C += Dir.Value;
				}

				// Only count as a sequence if 4 or more
				if (Sequence.Num() >= BaseSequenceLength)
				{
					//Check if this sequence is already accounted for
					bool bDuplicate = false;
					for (int32 Index : Sequence)
					{
						if (AlreadyCounted.Contains(Index))
						{
							bDuplicate = true;
							break;
						}
					}

					if (!bDuplicate)
					{
						for (int32 Index : Sequence)
						{
							AlreadyCounted.Add(Index);
						}

						AllSequences.Add(Sequence);
					}
				}
			}
		}
	}
	
	return AllSequences;
}

int32 UC4_GridLogicBase::ScoreSequence(const TArray<int32>& SequenceIndices)
{
	return BaseSequencePoints + FMath::Max(0, SequenceIndices.Num() - BaseSequenceLength) * BonusPointsPerExtraPiece;
}

void UC4_GridLogicBase::RemoveSequences(const TArray<TArray<int32>>& AllSequences)
{
	
	for (const TArray<int32>& Sequence : AllSequences)
	{
		for (int32 Index : Sequence)
		{
			Grid[Index] = 0;
		}
	}
}

void UC4_GridLogicBase::ShiftPiecesDown()
{
	for (int32 Col = 0; Col < NumColumns; Col++)
	{
		// Walk from the bottom row up, compacting non-zero values downward
		int32 WriteRow = NumRows - 1;

		for (int32 Row = NumRows - 1; Row >= 0; Row--)
		{
			if (Grid[GetIndex(Row, Col)] != 0)
			{
				Grid[GetIndex(WriteRow, Col)] = Grid[GetIndex(Row, Col)];

				if (WriteRow != Row)
				{
					Grid[GetIndex(Row, Col)] = 0;
				}

				WriteRow--;
			}
		}
	}
}

