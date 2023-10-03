/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomoya <ktomoya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:15:18 by ktomoya           #+#    #+#             */
/*   Updated: 2023/10/03 16:29:54 by ktomoya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

//int	main(int argc, char *argv[])
//{
//	if (argc != 2)
//		exit(1);
//	if (access(argv[1], R_OK) < 0)
//	{
//		printf("access error for %s\n", argv[1]);
//		exit(1);
//	}
//	else
//		printf("read access OK\n");
//	if (open(argv[1], O_RDONLY) < 0)
//	{
//		printf("open error for %s\n", argv[1]);
//		exit(1);
//	}
//	else
//		printf("open for reading OK\n");
//	exit(0);
//}

int main(int argc, char *argv[])
{
	if (argc != 2)
		exit(1);
	if (access(argv[1], R_OK) == 0)
		printf("%s は実行可能です。\n", argv[1]);
	else
	{
		if (errno == EACCES)
			printf("%s は読み込み権限がありません。\n", argv[1]);
		else if (errno == ENOENT)
			printf("%s は存在しません。\n", argv[1]);
		else
			perror("access");
	}
	return (0);
}

//int main() {
//	const char *filename = "a.txt";
//
//	// ファイルを作成し、読み取り専用で開く
//	int fd = open(filename, O_CREAT | O_RDONLY, 0444); // 0444 は読み取り専用の権限
//
//	if (fd == -1) {
//		perror("open");
//		return 1;
//	}
//
//	// access関数を使用してファイルの読み込み権限をチェック
//	if (access(filename, F_OK) == 0) {
//		printf("%s は読み込み可能です。\n", filename);
//	} else {
//		if (errno == EACCES) {
//			printf("%s は読み込み権限がありません。\n", filename);
//		} else if (errno == ENOENT) {
//			printf("%s は存在しません。\n", filename);
//		} else {
//			perror("access");
//		}
//	}
//
//	close(fd); // ファイルを閉じる
//
//	return 0;
//}