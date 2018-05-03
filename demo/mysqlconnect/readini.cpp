#include "readini.h"

int readIni::GetModuleFileName( char* sModuleName, char* sFileName, int nSize)
{
	int ret = -1;
	char sLine[1024] = { 0 };
	void* pSymbol = (void*)"";
	FILE *fp;
	char *pPath;

	fp = fopen ("/proc/self/maps", "r");
	if ( fp != NULL )
	{
		while (!feof (fp))
		{
			unsigned long start, end;

			if ( !fgets (sLine, sizeof (sLine), fp))
				continue;
			if ( !strstr (sLine, " r-xp ") || !strchr (sLine, '/'))
				continue;

			sscanf (sLine, "%lx-%lx ", &start, &end);
			if (pSymbol >= (void *) start && pSymbol < (void *) end)
			{
				char *tmp;
				size_t len;

				/* Extract the filename; it is always an absolute path */
				pPath = strchr (sLine, '/');

				/* Get rid of the newline */
				tmp = strrchr (pPath, '\n');
				if (tmp) *tmp = 0;

				/* Get rid of "(deleted)" */
				//len = strlen (pPath);
				//if (len > 10 && strcmp (pPath + len - 10, " (deleted)") == 0)
				//{
				// tmp = pPath + len - 10;
				// *tmp = 0;
				//}
				ret = 0;
				strcpy( sFileName, pPath );
			}
		}
		fclose (fp);

	}
	return ret;
}

int readIni::getCnfMess(char* pKey, char* pSave, char* pPath)
{
	FILE *fp;
	char sLine[1024] = { 0 };
	fp = fopen (pPath, "r");
	if ( fp != NULL )
	{
		while (!feof (fp))
		{
			unsigned long start, end;
			char *pCh = NULL;
			int nLen = 0;
			if ( !fgets (sLine, sizeof (sLine), fp))
				continue;
//			printf("-----%s---line--\n",sLine);
			if (strstr(sLine, pKey))
			{
				pCh = strchr(sLine,'=');
				nLen = pCh - sLine + 1;
				nLen = strlen(sLine) - nLen - 1;
				memcpy(pSave,pCh+1, nLen);
				break;
//				printf("----------%s--\n",pSave);
			}
		}
		fclose (fp);
	}
}