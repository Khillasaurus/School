//=================================================================================================
// Title:			UnitMove.cs
// Created By:		Daniel Schenker
// Date Created:	2012/11/07
// Last Edited:		2012/11/08
// Description:		A script which can be added to a unit so that the unit can follow waypoints.
//=================================================================================================

using UnityEngine;
using System.Collections;

/*
// Function Prototypes
 // General
public void StartMoving(float currentTime);
// Accessors
public float GetDefaultWaypointRadius();
public bool IsMoving();
public int GetLastWaypointReachedCount();
public float GetLastWaypointReachedTime();
public float GetWaypointRadius();
// Mutators
public void SetWaypointRadius(float radius);
 // Helper Functions
*/

public class UnitMove : MonoBehaviour
{
	//===---Public---===
	public float movementSpeed = 10.0f;
	public Vector3[] waypointList;

	//===---Private---===
	//State
	private bool mMoving = false;

	// Waypoint traversal
	private float mDefaultWaypointRadius = 0.1f;
	private Vector3 from;
	private Vector3 to;
	private int mLastWaypointReachedCount = 0;
	private float mLastWaypointReachedTime = -1;
	private float mWaypointRadius = 0.1f;

	//Debug
	public int testLaunchNum = 1;
	private string testKey;

	//=================================================================================================
	// Start
	//=================================================================================================

	void Start()
	{
		mMoving = false;
		mLastWaypointReachedCount = 0;
		mLastWaypointReachedTime = Time.time;

		//Set unit initial position to the start (first) waypoint
		rigidbody.position.Set(waypointList[0].x, waypointList[0].y, waypointList[0].z);

		//Set unit initial velocity
		movementSpeed = 10.0f;
		rigidbody.velocity.Set(movementSpeed, movementSpeed, movementSpeed);

		// Set Unit spawn position
		transform.rigidbody.position.Set(waypointList[0].x,
										 waypointList[0].y,
										 waypointList[0].z);

		from.Set(waypointList[0].x,
				 waypointList[0].y,
				 waypointList[0].z);

		to.Set(waypointList[1].x,
				 waypointList[1].y,
				 waypointList[1].z);
	}

	//=================================================================================================
	// Update
	//=================================================================================================

	void FixedUpdate()
	{
		// Toggle unit movement
		testKey = testLaunchNum.ToString();
		if(Input.GetKey(testKey))
		{
			StartMoving(Time.time);
		}

		if(mMoving)
		{
			//Check if the unit has reached the last waypoint
			if (mLastWaypointReachedCount == waypointList.Length - 1)
			{
				//Stop moving
				rigidbody.velocity.Set(0.0f, 0.0f, 0.0f);
				mMoving = false;
			}
			else
			{
				// Set from and to locations
				from.Set(waypointList[mLastWaypointReachedCount].x,
						 waypointList[mLastWaypointReachedCount].y,
						 waypointList[mLastWaypointReachedCount].z);

				to.Set(  waypointList[mLastWaypointReachedCount + 1].x,
						 waypointList[mLastWaypointReachedCount + 1].y,
						 waypointList[mLastWaypointReachedCount + 1].z);

				//Move unit
				transform.position = Vector3.MoveTowards(from, to, (Time.time - mLastWaypointReachedTime) * movementSpeed);

				// Check if unit has reached the next node
				if (rigidbody.position.x >= to.x - mWaypointRadius &&
					rigidbody.position.x < to.x + mWaypointRadius &&
					rigidbody.position.y >= to.y - mWaypointRadius &&
					rigidbody.position.y < to.y + mWaypointRadius &&
					rigidbody.position.z >= to.z - mWaypointRadius &&
					rigidbody.position.z < to.z + mWaypointRadius)
				{
					//Update what waypoint the unit is at
					++mLastWaypointReachedCount;

					//Set time the unit reached this waypoint
					mLastWaypointReachedTime = Time.time;

					//Update from location to be where the unit currently is
					from.Set(transform.rigidbody.position.x,
							 transform.rigidbody.position.y,
							 transform.rigidbody.position.z);

					//Update to location to the next waypoint, if it exits
					if (mLastWaypointReachedCount + 1 < waypointList.Length)
					{
						to.Set( waypointList[mLastWaypointReachedCount + 1].x,
								waypointList[mLastWaypointReachedCount + 1].y,
								waypointList[mLastWaypointReachedCount + 1].z);
					}
				}
			}
		}
	}

	//=================================================================================================
	// General
	//=================================================================================================

	public void StartMoving(float currentTime)
	{
		// If not already moving
		if(!mMoving)
		{
			// If there is at least a start and endpoint in the waypoint list
			if(waypointList.Length >= 2)
			{
				//Start moving
				mMoving = true;

				//Set time the unit reached the last waypoint
				mLastWaypointReachedTime = currentTime;
			}
		}
	}

	//=================================================================================================
	// Accessors
	//=================================================================================================

	public float GetDefaultWaypointRadius()
	{
		return mDefaultWaypointRadius;
	}

	//-------------------------------------------------------------------------------------------------

	public bool IsMoving()
	{
		return mMoving;
	}

	//-------------------------------------------------------------------------------------------------

	public int GetLastWaypointReachedCount()
	{
		return mLastWaypointReachedCount;
	}

	//-------------------------------------------------------------------------------------------------

	public float GetLastWaypointReachedTime()
	{
		return mLastWaypointReachedTime;
	}

	//-------------------------------------------------------------------------------------------------

	public float GetWaypointRadius()
	{
		return mWaypointRadius;
	}

	//=================================================================================================
	// Mutators
	//=================================================================================================

	public void SetWaypointRadius(float radius)
	{
		//Ensure radius is positive
		mWaypointRadius = (radius > 0) ? radius : mDefaultWaypointRadius;
	}

	//=================================================================================================
	// Helper Functions
	//=================================================================================================
}