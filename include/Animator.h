#pragma once
#include "raylib.h"

class Animator
{
public:
	/// <summary>Creates an animator instance.</summary>
	/// <param name="AnimatorName">A name the animator will be identified by.</param>
	/// <param name="NumOfFramesPerRow">The amount of frames/columns in a row.</param>
	/// <param name="NumOfRows">The amount of rows in the sprite sheet.</param>
	/// <param name="Speed">The animation speed in frames per second.</param>
	/// <param name="bPlayInReverse">Should the animator play the sprite in reverse play mode?</param>
	/// <param name="bContinuous">Should the animator automatically go to the next row in the sprite sheet?</param>
	/// <param name="bLooping">Should the animator loop indefinitely?</param>
	Animator(const char* AnimatorName, unsigned int NumOfFramesPerRow, unsigned int NumOfRows, unsigned int Speed, bool bPlayInReverse = false, bool bContinuous = false, bool bLooping = true);

	~Animator() = default;

	/// <summary>Assigns a sprite for the animator to use. (This should be called once)</summary>
	/// <param name="Sprite">The sprite the animator will use.</param>
	void AssignSprite(const Texture2D& Sprite);

	/// <summary>Changes the sprite the animator is using.</summary>
	/// <param name="NewSprite">The new sprite the animator will change to. Will reset to beginning frame.</param>
	/// <param name="NumOfFramesPerRow">The amount of frames/columns in a row.</param>
	/// <param name="NumOfRows">The amount of rows in the sprite sheet.</param>
	/// <param name="Speed">The animation speed in frames per second.</param>
	/// <param name="DelayInSeconds">The amount of time (in seconds) to change to the new sprite. A value of 0.0f is instant/no delay.</param>
	/// <param name="bPlayInReverse">Should the animator play the new sprite in reverse play mode?</param>
	/// <param name="bContinuous">Should the animator automatically go to the next row in the sprite sheet?</param>
	/// <param name="bLooping">Should the animator loop indefinitely?</param>
	void ChangeSprite(const Texture2D& NewSprite, unsigned int NumOfFramesPerRow, unsigned int NumOfRows, unsigned int Speed, float DelayInSeconds = 0.0f, bool bPlayInReverse = false, bool bContinuous = false, bool bLooping = true);

	/// <summary>Flips the sprite-sheet horizontally or vertically, or both.</summary>
	/// <param name="bHorizontalFlip">Flips the sprite sheet horizontally. DOES NOT WORK, set this to false.</param>
	/// <param name="bVerticalFlip">Flips the sprite sheet vertically.</param>
	void FlipSprite(bool bHorizontalFlip, bool bVerticalFlip = true);
	
	/// <summary>Set whether the animator should loop or not.</summary>
	/// <param name="bLooping">Should the animator loop?</param>
	void SetLooping(bool bLooping);

	/// <summary>Set whether the animator should go to the next row in the sprite sheet or not.</summary>
	/// <param name="bIsContinuous">Should the animator continue to the next row?</param>
	void SetContinuous(bool bIsContinuous);

	/// <summary>Set a new framerate the animator will use.</summary>
	/// <param name="NewFramerate">The new speed of animation.</param>
	void SetFramerate(unsigned int NewFramerate);

	/// <summary>Jump to a frame in the sprite-sheet.</summary>
	/// <param name="FrameNumber">The frame number in the sprite sheet. (Zero-based)</param>
	void GoToFrame(unsigned int FrameNumber);

	/// <summary>Jump to a row in the sprite-sheet.</summary>
	/// <param name="RowNumber">The row number in the sprite sheet. (Zero-based)</param>
	void GoToRow(unsigned int RowNumber);

	/// <summary>Jump to a column in the current row.</summary>
	/// <param name="ColumnNumber">The column number in the sprite sheet. (Zero-based)</param>
	void GoToColumn(unsigned int ColumnNumber);

	/// Jump to the first row.
	void GoToFirstRow();

	/// Jump to the first column.
	void GoToFirstColumn();

	/// Jump to the last row.
	void GoToLastRow();

	/// Jump to the last column.
	void GoToLastColumn();

	/// Jump to the first frame in the current row.
	void GoToFirstFrame();

	/// Jump to the last frame in the current row.
	void GoToLastFrame();

	/// Jump to the first frame in the sprite sheet.
	void GoToFirstFrameOfSpriteSheet();

	/// Jump to the last frame in the sprite sheet.
	void GoToLastFrameOfSpriteSheet();

	/// Jump to the next row index.
	void NextRow();

	/// Jump to the previous row index.
	void PreviousRow();

	/// Jump to the next column index.
	void NextColumn();

	/// Jump to the previous column index.
	void PreviousColumn();

	/// Play animation from the current frame.
	void Play();

	void LerpAnim(float Speed, bool bConstant);

	/// Start the animation when it has been paused or has been stopped.
	void Start();

	/// Stop the animation from playing.
	void Stop();

	/// <summary>Pause the animation.</summary>
	/// <param name="bToggle">If true, flip-flop between pausing and un-pausing the animation every time when called. If false, pause the animation. You need to call UnPause to start the animation again.</param>
	void Pause(bool bToggle = false);

	/// UnPause the animation. (Start playing)
	void UnPause();

	/// Set the play mode to forward.
	void Forward();

	/// <summary>Set the play mode to reverse.</summary>
	/// <param name="bToggle">If true, flip-flop between reversing and un-reversing the play mode every time when called. If false, reverse the play mode. You need to call Forward to un-reverse.</param>
	void Reverse(bool bToggle = false);
	
	/// Restart the animation from the beginning.
	void Restart();

	/// <returns>The total amount of frames in the sprite-sheet.</returns>
	unsigned int GetTotalFrames() const;

	/// <returns>The total rows in the sprite-sheet.</returns>
	unsigned int GetTotalRows() const;

	/// <returns>The total columns per row.</returns>
	unsigned int GetTotalColumns() const;

	/// <returns>The current frame the animator is on. (Zero based)</returns>
	unsigned int GetCurrentFrame() const;

	/// <returns>The current row the animator is on. (Zero based)</returns>
	unsigned int GetCurrentRow() const;

	/// <returns>The current column the animator is on. (Zero based)</returns>
	unsigned int GetCurrentColumn() const;

	/// <returns>The total time animation will take to finish in frames.</returns>
	unsigned int GetTotalTimeInFrames() const;

	/// <returns>The time remaining in frames.</returns>
	unsigned int GetTimeRemainingInFrames() const;

	/// <returns>The total time animation will take to finish in seconds.</returns>
	float GetTotalTimeInSeconds() const;

	/// <returns>The time remaining in seconds.</returns>
	float GetTimeRemainingInSeconds() const;

	/// <returns>The name of the animator.</returns>
	const char* GetName() const;

	/// <summary>Is the animator currently on the frame number specified?</summary>
	/// <param name="FrameNumber">The frame number to query. (Zero based)</param>
	/// <returns>If the animator is on the frame number specified, true. Otherwise, false.</returns>
	bool IsAtFrame(unsigned int FrameNumber) const;

	/// <summary>Is the animator currently on the row number specified?</summary>
	/// <param name="RowNumber">The row number to query. (Zero based)</param>
	/// <returns>If the animator is on the row number specified, true. Otherwise, false.</returns>
	bool IsAtRow(unsigned int RowNumber) const;

	/// <summary>Is the animator currently on the column number specified?</summary>
	/// <param name="ColumnNumber">The column number to query. (Zero based)</param>
	/// <returns>If the animator is on the column number specified, true. Otherwise, false.</returns>
	bool IsAtColumn(unsigned int ColumnNumber) const;

	/// <summary>Is the animator currently on the first frame of the sprite-sheet?</summary>
	/// <returns>If the animator is on the first frame of the sprite-sheet, true. Otherwise, false.</returns>
	bool IsAtFirstFrameOfSpriteSheet() const;

	/// <summary>Is the animator currently on the last frame of the sprite-sheet?</summary>
	/// <returns>If the animator is on the last frame of the sprite-sheet, true. Otherwise, false.</returns>
	bool IsAtLastFrameOfSpriteSheet() const;

	/// <summary>Is the animator currently on the first frame of a current row?</summary>
	/// <returns>If the animator is on the first frame, true. Otherwise, false.</returns>
	bool IsAtFirstFrame() const;

	/// <summary>Is the animator currently on the last frame of a current row?</summary>
	/// <returns>If the animator is on the last frame, true. Otherwise, false.</returns>
	bool IsAtLastFrame() const;

	/// <summary>Is the animator currently on the first row of the sprite-sheet?</summary>
	/// <returns>If the animator is on the first row, true. Otherwise, false.</returns>
	bool IsAtFirstRow() const;

	/// <summary>Is the animator currently on the first column of a current row?</summary>
	/// <returns>If the animator is on the first column, true. Otherwise, false.</returns>
	bool IsAtFirstColumn() const;

	/// <summary>Is the animator currently on the last row of the sprite-sheet?</summary>
	/// <returns>If the animator is on the last row, true. Otherwise, false.</returns>
	bool IsAtLastRow() const;

	/// <summary>Is the animator currently on the last column of a current row?</summary>
	/// <returns>If the animator is on the last column, true. Otherwise, false.</returns>
	bool IsAtLastColumn() const;

	/// <summary>Is the animator currently playing?</summary>
	/// <returns>If the animator is currently playing, true. Otherwise, false.</returns>
	bool IsPlaying() const;

	/// <summary>Has the animator started playing?</summary>
	/// <returns>If the animator started playing, true. Otherwise, false.</returns>
	bool IsStartedPlaying();

	/// <summary>Has the animator finished playing?</summary>
	/// <returns>If the animator has animator finished playing, true. Otherwise, false.</returns>
	bool IsFinishedPlaying();

	/// <returns>The Frame rectangle. (Used for drawing the sprite)</returns>
	Rectangle GetFrameRec() const;

	/// <returns>The sprite texture.</returns>
	Texture2D GetSprite() const;

private:
	/// Counts down in frames. Used for timing functionality.
	void CountdownInFrames();

	/// Resets the timer to beginning.
	void ResetTimer();

	/// Resets the frame rectangle properties.
	void ResetFrameRec();

	/// Jumps to the next frame in the sprite-sheet.
	void NextFrame();

	/// Jumps to the previous frame in the sprite-sheet.
	void PreviousFrame();

	float Lerp(float Start, float End, float Alpha);

	/// Sprite width / Total columns per row
	float FrameWidth{};

	/// Sprite height / Total rows
	float FrameHeight{};

	/// Used for timing.
	float TimeRemainingFramesCounter{};

	/// Used for querying how many frames have passed.
	unsigned int PlaybackPosition;

	/// Used for changing sprite if the delay parameter is used in ChangeSprite() function.
	unsigned int DelayFramesCounter;

	/// Total amount of rows.
	unsigned int Rows;

	/// Total amount of columns.
	unsigned int Columns;

	/// Speed of animation.
	unsigned int Framerate;

	/// The current row the animator is on. (Zero based)
	unsigned int CurrentRow;

	/// The current column the animator is on. (Zero based)
	unsigned int CurrentColumn;

	/// The current frame the animator is on. (Zero based)
	unsigned int CurrentFrame;

	/// Should flip the sprite horizontally?
	bool bFlipH{};

	/// Should flip the sprite vertically?
	bool bFlipV{};

	/// Used to query whether the animator is looping or not.
	bool bCanLoop;

	/// Used to query whether the animator is in reverse mode or not.
	bool bReverse{};

	/// Used to query whether the animator should go to the next row in the sprite-sheet.
	bool bContinuous{};

	/// Used to query whether the animator is paused or not.
	bool bPaused{};

	/// Used to query whether the animator is finished playing or not.
	bool bIsAnimationFinished{};

	/// Used to query whether the animator has started playing or not.
	bool bHasStartedPlaying{};

	/// The frame rectangle is used to draw only a part of the whole sprite-sheet
	Rectangle FrameRec{};

	/// The sprite the animator is using
	Texture2D Sprite{};
	
	/// The name of this animator
	const char* Name{};
};